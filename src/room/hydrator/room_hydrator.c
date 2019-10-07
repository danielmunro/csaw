int id_from_pgresult(PGresult *result, int row, int index) {
    char *pEnd;
    return strtol(PQgetvalue(result, row, index), &pEnd, 10);
}

Room *hydrate_room(PGresult *result, int row) {
    uuid_t uuid;
    uuid_parse(PQgetvalue(result, row, 1), uuid);
    return create_room(
            id_from_pgresult(result, row, 0),
            uuid,
            PQgetvalue(result, row, 2));
}

Exit *hydrate_exit(RoomTable *room_table, PGresult *result, int row) {
    return create_exit(
            id_from_pgresult(result, row, 0),
            get_room(room_table, strtol(PQgetvalue(result, row, 1), 0, 10)),
            get_room(room_table, strtol(PQgetvalue(result, row, 2), 0, 10)),
            get_direction_from_string(PQgetvalue(result, row, 3)));
}

void hydrate_exits(RoomTableT *room_table, RoomT *room, PGresult *result) {
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
