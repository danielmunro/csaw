struct Action {
    enum ActionType action_type;
    char * name;
    void (*action)(GameServiceT *game_service, Request *request);
};

ActionT *create_action(enum ActionType action_type, char * name, void (*action)(GameServiceT *game_service, Request *request)) {
    ActionT *a = malloc(sizeof(struct Action));
    a->action_type = action_type;
    a->name = name;
    a->action = action;
    return a;
}