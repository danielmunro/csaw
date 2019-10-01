typedef struct {
    enum ActionType action_type;
    Mob *mob;
    char * buffer;
} Request;

Request *create_request(enum ActionType action_type, Mob *mob, char * buffer) {
    Request *r = malloc(sizeof(Request));
    r->action_type = action_type;
    r->mob = mob;
    r->buffer = buffer;
    return r;
}