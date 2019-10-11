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
    puts("start is mob in array");
    for (int i = 0; i < MAX_MOBS_PER_ROOM; i++) {
        printf("is_mob_in_array %d\n", i);
        if (mobs[i] && mobs[i] == mob) {
            return i;
        }
    }
    return -1;
}

void remove_mob_from_room(LocationTable *location_table, Mob *mob) {
    if (mob->room) {
        puts("remove mob from current room");
        int index = is_mob_in_array(location_table->rooms[mob->room->id], mob);
        printf("index found: %d\n", index);
        if (index > -1) {
            location_table->rooms[mob->room->id][index] = NULL;
        }
        mob->room = NULL;
    }
    puts("done remove mob");
}

void add_mob_location(LocationTable *location_table, Mob *mob, RoomT *room) {
    printf("add mob to room %d\n", room->id);
    remove_mob_from_room(location_table, mob);
    for (int i = 0; i < MAX_MOBS_PER_ROOM; i++) {
        printf("add loop index %d\n", i);
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

int get_mob_room_id(LocationTable *location_table, Mob *mob) {
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (location_table->rooms[i] && is_mob_in_array(location_table->rooms[i], mob)) {
            return i;
        }
    }
    return -1;
}
