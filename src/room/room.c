#define ROOM_NAME_MAX_LENGTH 200
#define ROOM_DESCRIPTION_MAX_LENGTH 2048

typedef struct Room {
    int id;
    uuid_t uuid;
    char name[ROOM_NAME_MAX_LENGTH];
    Exit *exits[MAX_EXITS];
} Room;

Room *create_room(int id, uuid_t uuid, char *name) {
    Room *room = malloc(sizeof(Room));
    room->id = id;
    uuid_copy(room->uuid, uuid);
    strcpy(room->name, name);
    for (int i = 0; i < MAX_EXITS; i++) {
        room->exits[i] = NULL;
    }
    return room;
}

int get_room_id(Room *room) {
    return room->id;
}

char *room_to_string(Room *room, LocationTableT *location_table) {
    char *out = (char *) malloc(ROOM_DESCRIPTION_MAX_LENGTH * sizeof(char));
    sprintf(out, "%s\nExits [", room->name);
    for (int j = 0; j < MAX_EXITS; j++) {
        if (room->exits[j]) {
            strncat(out, get_string_from_direction(room->exits[j]->direction), 1);
        }
    }
    strcat(out, "]\n");
    for (int i = 0; i < MAX_MOBS_PER_ROOM; i++) {
        Mob *mob = get_mob_by_room_and_index(location_table, room, i);
        if (mob) {
            strcat(out, mob->name);
            strcat(out, " is here.\n");
        }
    }
    return out;
}
