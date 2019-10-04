PGresult *fetch_all_mobs() {
    return PQexec(conn, query_all_mobs);
}

PGresult *fetch_all_rooms() {
    return PQexec(conn, query_all_rooms);
}

PGresult *fetch_exits_for_room(RoomT *room) {
    char *param = "";
    sprintf(param, "%d", get_room_id(room));
    return PQexec(conn, strcat(query_room_exits, param));
}