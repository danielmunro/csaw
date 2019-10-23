#define LOOP_DELAY_USEC 10000

enum GameServiceStatus { Initialized = 1, Running = 2, Stopped = 3 };

typedef struct GameService {
    Server *server;
    EventDispatcher *event_dispatcher;
    ActionTable *action_table;
    MobTable *mob_template_table;
    MobTable *mob_table;
    RoomTable *room_table;
    LocationTable *location_table;
    MobResetTable *mob_reset_table;
    TimeService *time_service;
    enum GameServiceStatus status;
} GameService;

GameServiceT *create_game_service() {
    GameServiceT *g = malloc(sizeof(struct GameService));
    g->server = create_server();
    g->event_dispatcher = create_event_dispatcher();
    g->action_table = create_action_table();
    g->mob_template_table = create_mob_template_table();
    g->mob_table = create_mob_table();
    g->room_table = create_room_table();
    g->location_table = create_location_table();
    g->mob_reset_table = create_hydrated_mob_reset_table(g);
    g->time_service = create_time_service();
    g->status = Initialized;
    return g;
}

void register_event_consumers(EventDispatcher *event_dispatcher) {
    event_dispatcher->consumers[0] = create_input_to_action_event_consumer();
    event_dispatcher->consumers[1] = create_dummy_login_event_consumer();
    event_dispatcher->consumers[2] = create_pulse_to_tick_event_consumer();
    event_dispatcher->consumers[3] = create_increment_ticks_event_consumer();
    event_dispatcher->consumers[4] = create_reset_mobs_event_consumer();
}

void reset_mobs(GameService *game_service) {
    debug_puts("reset_mobs running");
    for (int i = 0; i < MAX_MOB_RESETS; i++) {
        debug_printf("index %d\n", i);
        if (!game_service->mob_reset_table->resets[i]) {
            return;
        }
        do_mob_reset(game_service, game_service->mob_reset_table->resets[i]);
    }
    debug_puts("reset_mobs done");
}

LocationTable *get_location_table(GameServiceT *game_service) {
    return game_service->location_table;
}

MobTable *get_mob_table(GameServiceT *game_service) {
    return game_service->mob_table;
}

Server *get_server(GameServiceT *game_service) {
    return game_service->server;
}

ClientT *get_client(GameServiceT *game_service, int i) {
    return game_service->server->clients[i];
}

ClientT *get_client_from_mob(GameServiceT *game_service, Mob *mob) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (game_service->server->clients[i] && game_service->server->clients[i]->mob == mob) {
            return game_service->server->clients[i];
        }
    }
    return NULL;
}

int word_matches_action(GameServiceT *game_service, ActionT *action, enum Word word, EventT *event, char *input) {
    if (!word) {
        return 0;
    }
    if (word == ActionWord) {
        return strncmp(action->name, input, strlen(input)) == 0;
    }
    if (word == MobInRoomWord) {
        for (int i = 0; i < MAX_MOBS_PER_ROOM; i++) {
            Mob *mob = get_mob_by_room_and_index(game_service->location_table, event->mob->room, i);
            if (!mob) {
                return 0;
            }
            if (strcmp(mob->description->name, input) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int words_match_action(GameServiceT *game_service, ActionT *action, EventT *event) {
    char str[strlen(event->buffer)];
    strcpy(str, event->buffer);
    char *word = strtok(str, " ");
    for (int j = 0; j < MAX_WORDS; j++) {
        if (!action->words->word[j]) {
            return word == NULL;
        }
        if (!word || !word_matches_action(game_service, action, action->words->word[j], event, word)) {
            return 0;
        }
        word = strtok(NULL, " ");
    }
    return 1;
}

ActionT *get_action_from_input_event(GameServiceT *game_service, Event *event) {
    for (int i = 0; i < MAX_ACTIONS; i++) {
        ActionT *action = game_service->action_table->actions[i];
        if (action && words_match_action(game_service, action, event)) {
            return action;
        }
    }
    return NULL;
}

void dispatch_event(GameServiceT *game_service, Event *event) {
    for (int i = 0; i < MAX_EVENT_CONSUMERS; i++) {
        if (!game_service->event_dispatcher->consumers[i]) {
            return;
        }
        if (ready_to_consume(game_service->event_dispatcher->consumers[i], event)) {
            game_service->event_dispatcher->consumers[i]->consume(game_service, event);
            if (event->status == TerminatedEventStatus) {
                return;
            }
        }
    }
}

void check_client_buffers(GameServiceT *g) {
    ClientReadBuffers *bufs = read_client_buffers(g->server);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (bufs->buffers[i]) {
            debug_printf("buffer found for client %d: %s\n", bufs->buffers[i]->client->socket, bufs->buffers[i]->buffer);
            Event *event = create_client_input_event(
                    bufs->buffers[i]->client, bufs->buffers[i]->buffer);
            dispatch_event(g, event);
            free(event);
        }
    }
    free(bufs);
}

void dispatch_pulse_event(GameServiceT *game_service) {
    Event *event = create_pulse_event();
    dispatch_event(game_service, event);
    free(event);
}

void start_game_service(GameServiceT *g) {
    g->status = Running;
    debug_puts("start game loop");
    while(g->status == Running) {
        loop_server(g);
        check_client_buffers(g);
        int elapsed_seconds = increment_time(g->time_service);
        if (elapsed_seconds > 0) {
            dispatch_pulse_event(g);
        }
        usleep(LOOP_DELAY_USEC);
    }
}

void client_send_to_clients(GameServiceT *g, ClientT *c, char *buffer) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (g->server->clients[i] && g->server->clients[i] != c) {
            send_to_client(g->server->clients[i], buffer);
        }
    }
}

Mob *get_mob_template_by_id(GameServiceT *game_service, int id) {
    for (int i = 0 ; i < MAX_MOBS; i++) {
        if (game_service->mob_template_table->mobs[i] && game_service->mob_template_table->mobs[i]->id == id) {
            return game_service->mob_template_table->mobs[i];
        }
    }
    return NULL;
}

Room *get_room_by_id(GameServiceT *g, int id) {
    for (int i = 0 ; i < MAX_ROOMS; i++) {
        if (g->room_table->rooms[i] && g->room_table->rooms[i]->id == id) {
            return g->room_table->rooms[i];
        }
    }
    return NULL;
}
