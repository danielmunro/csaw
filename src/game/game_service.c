enum GameServiceStatus { Initialized = 1, Running = 2, Stopped = 3 };

struct GameService {
    Server *server;
    EventDispatcher *event_dispatcher;
    ActionTable *action_table;
    MobTable *mob_table;
    RoomTable *room_table;
    LocationTable *location_table;
    enum GameServiceStatus status;
};

GameServiceT *create_game_service() {
    GameServiceT *g = malloc(sizeof(struct GameService));
    g->server = create_server();
    g->event_dispatcher = create_event_dispatcher();
    g->action_table = create_action_table();
    g->mob_table = create_mob_table();
    g->room_table = create_room_table();
    g->location_table = create_location_table();
    g->status = Initialized;
    return g;
}

Room *get_mob_room(GameServiceT *game_service, Mob *mob) {
    int id = get_mob_room_id(game_service->location_table, mob);
    if (id) {
        for (int i = 0; i < MAX_ROOMS; i++) {
            if (game_service->room_table->rooms[i] && game_service->room_table->rooms[i]->id == id) {
                return game_service->room_table->rooms[i];
            }
        }
    }
    return NULL;
}

ClientT *get_client(GameServiceT *game_service, int i) {
    return game_service->server->clients[i];
}

int input_matches_action(ActionT *action, char *name_partial) {
    return action && strncmp(action->name, name_partial, strlen(name_partial)) == 0;
}

ActionT *get_action(GameServiceT *game_service, char *name_partial) {
    for (int i = 0; i < MAX_ACTIONS; i++) {
        if (input_matches_action(game_service->action_table->actions[i], name_partial)) {
            return game_service->action_table->actions[i];
        }
    }
    return 0;
}

void dispatch_event(GameServiceT *game_service, Event *event) {
    for (int i = 0; i < MAX_EVENT_CONSUMERS; i++) {
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
            Event *event = create_client_input_event(
                    bufs->buffers[i]->client, bufs->buffers[i]->buffer);
            dispatch_event(g, event);
            free(event);
        }
    }
    free(bufs);
}

void start_game_service(GameServiceT *g) {
    g->status = Running;
    puts("starting game loop");
    while(g->status == Running) {
        loop_server(g->server);
        check_client_buffers(g);
    }
}

void client_send_to_clients(GameServiceT *g, ClientT *c, char *buffer) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (g->server->clients[i] && g->server->clients[i] != c) {
            send_to_client(g->server->clients[i], buffer);
        }
    }
}