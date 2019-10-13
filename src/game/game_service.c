enum GameServiceStatus { Initialized = 1, Running = 2, Stopped = 3 };

typedef struct GameService {
    Server *server;
    EventDispatcher *event_dispatcher;
    ActionTable *action_table;
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
    g->mob_table = create_mob_table();
    g->room_table = create_room_table();
    g->location_table = create_location_table();
    g->mob_reset_table = create_mob_reset_table(g);
    g->time_service = create_time_service();
    g->status = Initialized;
    return g;
}

void register_event_consumers(EventDispatcher *event_dispatcher) {
    event_dispatcher->consumers[0] = create_input_to_action_event_consumer();
    event_dispatcher->consumers[1] = create_dummy_login_event_consumer();
    event_dispatcher->consumers[2] = create_pulse_to_tick_event_consumer();
}

LocationTable *get_location_table(GameServiceT *game_service) {
    return game_service->location_table;
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

ActionT *get_action(GameServiceT *game_service, char *name_partial) {
    for (int i = 0; i < MAX_ACTIONS; i++) {
        ActionT *action = game_service->action_table->actions[i];
        if (action && strncmp(action->name, name_partial, strlen(name_partial)) == 0) {
            return game_service->action_table->actions[i];
        }
    }
    return NULL;
}

void dispatch_event(GameServiceT *game_service, Event *event) {
    debug_printf("dispatching event type %d\n", event->event_type);
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
    debug_puts("start check_client_buffers");
    ClientReadBuffers *bufs = read_client_buffers(g->server);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (bufs->buffers[i]) {
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
    }
}

void client_send_to_clients(GameServiceT *g, ClientT *c, char *buffer) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (g->server->clients[i] && g->server->clients[i] != c) {
            send_to_client(g->server->clients[i], buffer);
        }
    }
}

Mob *get_mob_by_id(GameServiceT *g, int id) {
    for (int i = 0 ; i < MAX_MOBS; i++) {
        if (g->mob_table->mobs[i] && g->mob_table->mobs[i]->id == id) {
            return g->mob_table->mobs[i];
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
