enum GameServiceStatus { Initialized = 1, Running = 2, Stopped = 3 };

struct GameService {
    Server *server;
    EventDispatcher *event_dispatcher;
    ActionTable *action_table;
    MobTable *mob_table;
    RoomTable *room_table;
    LocationTable *location_table;
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
    g->status = Initialized;
    return g;
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

ActionT *get_action(GameServiceT *game_service, char *name_partial) {
    printf("get_action sanity, name partial: %s\n", name_partial);
    for (int i = 0; i < MAX_ACTIONS; i++) {
        ActionT *action = game_service->action_table->actions[i];
        if (action && strncmp(action->name, name_partial, strlen(name_partial)) == 0) {
            printf("action: %s, input: %s, input length: %lu\n", action->name, name_partial, strlen(name_partial));
            return game_service->action_table->actions[i];
        }
    }
    return NULL;
}

void dispatch_event(GameServiceT *game_service, Event *event) {
    printf("dispatching event for %d\n", event->event_type);
    for (int i = 0; i < MAX_EVENT_CONSUMERS; i++) {
        printf("event consumer index %d\n", i);
        if (!game_service->event_dispatcher->consumers[i]) {
            puts("done with event consumers");
            return;
        }
        puts("proceeding");
        if (ready_to_consume(game_service->event_dispatcher->consumers[i], event)) {
            puts("consuming event");
            game_service->event_dispatcher->consumers[i]->consume(game_service, event);
            if (event->status == TerminatedEventStatus) {
                return;
            }
        }
    }
}

void check_client_buffers(GameServiceT *g) {
    puts("start check client buffers");
    ClientReadBuffers *bufs = read_client_buffers(g->server);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (bufs->buffers[i]) {
            printf("buffer %d\n", i);
            Event *event = create_client_input_event(
                    bufs->buffers[i]->client, bufs->buffers[i]->buffer);
            dispatch_event(g, event);
            free(event);
            puts("event dispatched");
        }
    }
    puts("done checking buffers");
    free(bufs);
}

void start_game_service(GameServiceT *g) {
    g->status = Running;
    puts("starting game loop");
    while(g->status == Running) {
        loop_server(g);
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