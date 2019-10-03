Room *hydrate_room(PGresult *result, int row) {
    char * pEnd;
    return create_room(
            strtol(PQgetvalue(result, row, 0), &pEnd, 10),
            uuid_from_string(PQgetvalue(result, row, 1)),
            PQgetvalue(result, row, 2));
}

RoomTable *hydrate_room_table(PGresult *result) {
    int rows = PQntuples(result);
    RoomTable *room_table = malloc(sizeof(RoomTable));
    for(int i = 0; i < rows; i++) {
        room_table->rooms[i] = hydrate_room(result, i);
    }
    return room_table;
}
