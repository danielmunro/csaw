#define QUERY_MAX_LENGTH 2048

PGresult *fetch_all_mobs() {
    return PQexec(conn, query_all_mobs);
}

PGresult *fetch_all_rooms() {
    return PQexec(conn, query_all_rooms);
}

char *create_room_query(int room_id) {
    char *query;
    query = (char *) malloc(QUERY_MAX_LENGTH);
    sprintf(query, "%s%d", query_room_exits, room_id);
    return query;
}

PGresult *fetch_exits_for_room(RoomT *room) {
    char *query = create_room_query(get_room_id(room));
    PGresult *result = PQexec(conn, query);
    free(query);
    return result;
}