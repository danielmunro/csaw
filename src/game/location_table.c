typedef struct LocationTable {
    Mob *rooms[MAX_ROOMS][MAX_MOBS_PER_ROOM];
} LocationTable;

LocationTable *create_location_table() {
    return malloc(sizeof(LocationTable));
}

int is_mob_in_array(Mob *mobs[MAX_MOBS_PER_ROOM], Mob *mob) {
    for (int i = 0; i < MAX_MOBS_PER_ROOM - 1; i++) {
        if (mobs[i] && mobs[i] == mob) {
            return i;
        }
    }
    return -1;
}

void remove_mob_from_room(LocationTable *location_table, Mob *mob) {
    if (mob->room) {
        int room_id = get_room_id(mob->room);
        int index = is_mob_in_array(location_table->rooms[room_id], mob);
        if (index) {
            location_table->rooms[room_id][index] = NULL;
        }
        mob->room = NULL;
    }
}

void add_mob_location(LocationTable *location_table, Mob *mob, RoomT *room) {
    int id = get_room_id(room);
    remove_mob_from_room(location_table, mob);
    for (int i = 0; i < MAX_MOBS_PER_ROOM; i++) {
        if (!location_table->rooms[id][i]) {
            location_table->rooms[id][i] = mob;
            mob->room = room;
            return;
        }
    }
}

void move_mob(LocationTable *location_table, Mob *mob, RoomT *room, enum Direction direction) {
    for (int i = 0; i < MAX_EXITS; i++) {
        if (room->exits[i] && room->exits[i]->direction == direction) {
            add_mob_location(location_table, mob, room->exits[i]->destination);
        }
    }
}

int get_mob_room_id(LocationTable *location_table, Mob *mob) {
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (location_table->rooms[i] && is_mob_in_array(location_table->rooms[i], mob)) {
            return i;
        }
    }
    return -1;
}
