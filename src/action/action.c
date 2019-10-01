typedef struct {
    enum ActionType request_type;
    char * name;
    void (*action)(GameServiceT *game_service, Request *request);
} Action;

Action *create_action(enum ActionType request_type, char * name, void (*action)(GameServiceT *game_service, Request *request)) {
    Action *a = malloc(sizeof(Action));
    a->request_type = request_type;
    a->name = name;
    a->action = action;
    return a;
}