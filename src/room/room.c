#define MAX_EXITS 6

typedef struct Room {
    int id;
    UuidT uuid;
    char name[200];
    Exit *exits[MAX_EXITS];
} Room;

Room *create_room(int id, UuidT *uuid, char *name) {
    Room *room = malloc(sizeof(Room));
    room->id = id;
    uuid_copy(room->uuid.uuid, uuid->uuid);
    strcpy(room->name, name);
    return room;
}

int get_room_id(Room *room) {
    return room->id;
}

char *room_to_string(Room *room) {
    char *out;
    out = (char *) malloc(100);
    strcat(out, room->name);
    strcat(out, "\nExits [");
    for (int j = 0; j < MAX_EXITS - 1; j++) {
        if (room->exits[j]) {
            strncat(out, room->exits[j]->direction, 1);
        }
    }
    strcat(out, "]");
    return out;
}
