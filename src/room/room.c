#define MAX_EXITS 6

typedef struct Room {
    int id;
    char *name;
    Exit *exits[MAX_EXITS];
} Room;

Room *create_room(int id, char *name) {
    Room *room = malloc(sizeof(Room));
    room->id = id;
    room->name = name;
    return room;
}

void set_exits(Room *room, Exit *exits[]) {
    memcpy(room->exits, exits, sizeof *exits);
}
