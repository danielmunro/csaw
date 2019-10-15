typedef struct LocationTable {
    Mob *rooms[MAX_ROOMS][MAX_MOBS_PER_ROOM];
} LocationTable;

LocationTable *create_location_table() {
    LocationTable *location_table = malloc(sizeof(LocationTable));
    for (int i = 0; i < MAX_ROOMS; i++) {
        Mob *rooms[MAX_MOBS_PER_ROOM] = {};
        memcpy(location_table->rooms[i], rooms, 0);
    }
    return location_table;
}

int is_mob_in_array(Mob *mobs[MAX_MOBS_PER_ROOM], Mob *mob) {
    for (int i = 0; i < MAX_MOBS_PER_ROOM; i++) {
        if (mobs[i] && mobs[i] == mob) {
            return i;
        }
    }
    return -1;
}

void remove_mob_from_room(LocationTable *location_table, Mob *mob) {
    if (!mob->room) {
        return;
    }
    debug_printf("remove mob from room %d\n", mob->room->id);
    int index = is_mob_in_array(location_table->rooms[mob->room->id], mob);
    if (index > -1) {
        location_table->rooms[mob->room->id][index] = NULL;
    }
    mob->room = NULL;
}

void add_mob_location(LocationTable *location_table, Mob *mob, RoomT *room) {
    debug_printf("add mob to room %d\n", room->id);
    remove_mob_from_room(location_table, mob);
    for (int i = 0; i < MAX_MOBS_PER_ROOM; i++) {
        if (!location_table->rooms[room->id][i]) {
            location_table->rooms[room->id][i] = mob;
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

int count_mobs_in_room_by_mob(LocationTable *location_table, Mob *mob) {
    int in_room = 0;
    for (int i = 0; i < MAX_MOBS_PER_ROOM; i++) {
        if (location_table->rooms[mob->room->id][i] &&
            location_table->rooms[mob->room->id][i]->canonical_id == mob->canonical_id) {
            in_room++;
        }
    }
    return in_room;
}
