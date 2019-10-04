Room *hydrate_room(PGresult *result, int row) {
    char *pEnd;
    return create_room(
            strtol(PQgetvalue(result, row, 0), &pEnd, 10),
            uuid_from_string(PQgetvalue(result, row, 1)),
            PQgetvalue(result, row, 2));
}

Exit *hydrate_exit(RoomTable *room_table, PGresult *result, int row) {
    char *pEnd;
    return create_exit(
            strtol(PQgetvalue(result, row, 0), &pEnd, 10),
            get_room(room_table, strtol(PQgetvalue(result, row, 1), 0, 10)),
            get_room(room_table, strtol(PQgetvalue(result, row, 2), 0, 10)),
            PQgetvalue(result, row, 3));
}

void *hydrate_exits(RoomTableT *room_table, RoomT *room, PGresult *result) {
    int rows = PQntuples(result);
    for (int i = 0; i < rows; i++) {
        room->exits[i] = hydrate_exit(room_table, result, i);
    }
}

RoomTable *hydrate_room_table(PGresult *result) {
    int rows = PQntuples(result);
    RoomTable *room_table = malloc(sizeof(RoomTable));
    for (int i = 0; i < rows; i++) {
        room_table->rooms[i] = hydrate_room(result, i);
    }
    for (int i = 0; i < rows; i++) {
        hydrate_exits(
                room_table,
                room_table->rooms[i],
                fetch_exits_for_room(room_table->rooms[i]));
    }
    return room_table;
}
