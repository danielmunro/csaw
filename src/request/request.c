typedef struct {
    enum ActionType request_type;
    Mob *mob;
    char * buffer;
} Request;

Request *create_request(enum ActionType request_type, Mob *mob, char * buffer) {
    Request *r = malloc(sizeof(Request));
    r->request_type = request_type;
    r->mob = mob;
    r->buffer = buffer;
    return r;
}