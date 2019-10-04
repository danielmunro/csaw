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

void add_mob_location(GameServiceT *game_service, Mob *mob, Room *room) {
    for (int i = 0; i < MAX_MOBS_PER_ROOM; i++) {
        if (!game_service->location_table->rooms[room->id][i]) {
            game_service->location_table->rooms[room->id][i] = mob;
            mob->room = room;
            return;
        }
    }
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
    ClientReadBuffers *clientReadBuffers = read_client_buffers(g->server);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clientReadBuffers->buffers[i]) {
            dispatch_event(g, create_client_input_event(
                    clientReadBuffers->buffers[i]->client, clientReadBuffers->buffers[i]->buffer));
        }
    }
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