#define MAX_EXITS 6

typedef struct Room {
    int id;
    UuidT uuid;
    char *name;
    Exit *exits[MAX_EXITS];
} Room;

Room *create_room(int id, UuidT *uuid, char *name) {
    Room *room = malloc(sizeof(Room));
    room->id = id;
    uuid_copy(room->uuid.uuid, uuid->uuid);
    room->name = name;
    return room;
}

void set_exits(Room *room, Exit *exits[]) {
    memcpy(room->exits, exits, sizeof *exits);
}
