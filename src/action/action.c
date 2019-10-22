struct Action {
    enum ActionType action_type;
    char *name;
    Words *words;
    void (*action)(GameServiceT *game_service, RequestT *request);
};

ActionT *create_action(enum ActionType action_type, char * name, Words *words, void (*action)(GameServiceT *game_service, RequestT *request)) {
    ActionT *a = malloc(sizeof(struct Action));
    a->action_type = action_type;
    a->name = name;
    a->words = words;
    a->action = action;
    return a;
}
