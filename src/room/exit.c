typedef struct Exit {
    int id;
    RoomT *source;
    RoomT *destination;
    enum Direction direction;
} Exit;

Exit *create_exit(int id, RoomT *source, RoomT *destination, enum Direction direction) {
    Exit *e = malloc(sizeof(Exit));
    e->id = id;
    e->source = source;
    e->destination = destination;
    e->direction = direction;
    return e;
}