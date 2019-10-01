enum GameServiceStatus { Initialized = 1, Running = 2, Stopped = 3 };

typedef struct GameService {
    Server *server;
    EventDispatcher *event_dispatcher;
    ActionTable *action_table;
    enum GameServiceStatus status;
} GameService;

GameService *create_game_service() {
    GameService *g = malloc(sizeof(GameService));
    g->server = create_server();
    g->event_dispatcher = create_event_dispatcher();
    g->action_table = create_action_table();
    g->status = Initialized;
    return g;
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

void check_client_buffers(GameService *g) {
    ClientReadBuffers *clientReadBuffers = read_client_buffers(g->server);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clientReadBuffers->buffers[i]) {
            dispatch_event(g, create_client_input_event(
                    clientReadBuffers->buffers[i]->client, clientReadBuffers->buffers[i]->buffer));
        }
    }
}

void start_game_service(GameService *g) {
    g->status = Running;
    while(g->status == Running) {
        loop_server(g->server);
        check_client_buffers(g);
    }
}