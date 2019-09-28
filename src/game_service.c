enum GameServiceStatus { Initialized = 1, Running = 2, Stopped = 3 };

typedef struct {
    Server *server;
    EventDispatcher *event_dispatcher;
    enum GameServiceStatus status;
} GameService;

GameService *create_game_service() {
    GameService *g = malloc(sizeof(GameService));
    g->server = create_server();
    g->event_dispatcher = create_event_dispatcher();
    g->status = Initialized;
    return g;
}

void start_game_service(GameService *g) {
    g->status = Running;
    while(g->status == Running) {
        loop_server(g->server);
        ClientReadBuffers *clientReadBuffers = read_client_buffers(g->server);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clientReadBuffers->buffers[i]) {
                Event *event = create_client_input_event(
                        clientReadBuffers->buffers[i]->client, clientReadBuffers->buffers[i]->buffer);
                dispatch_event(g->event_dispatcher, event);
            }
        }
    }
}