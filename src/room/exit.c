typedef struct Exit {
    int id;
    RoomT *source;
    RoomT *destination;
    char *direction;
} Exit;

Exit *create_exit(int id, RoomT *source, RoomT *destination, char *direction) {
    Exit *e = malloc(sizeof(Exit));
    e->id = id;
    e->source = source;
    e->destination = destination;
    e->direction = direction;
    return e;
}