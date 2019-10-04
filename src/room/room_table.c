typedef struct RoomTable {
    RoomT *rooms[MAX_ROOMS];
} RoomTable;

RoomTable *create_room_table() {
    PGresult *res = fetch_all_rooms();
    RoomTable *room_table = hydrate_room_table(res);
    PQclear(res);
    return room_table;
}

Room *get_room(RoomTable *room_table, int id) {
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (room_table->rooms[i] && room_table->rooms[i]->id == id) {
            return room_table->rooms[i];
        }
    }
    return 0;
}
