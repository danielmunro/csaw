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
    }
}