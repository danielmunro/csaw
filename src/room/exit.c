typedef struct Exit {
    int id;
    RoomT *source;
    RoomT *destination;
} Exit;

Exit *create_exit(int id, RoomT *source, RoomT *destination) {
    Exit *e = malloc(sizeof(Exit));
    e->id = id;
    e->source = source;
    e->destination = destination;
    return e;
}