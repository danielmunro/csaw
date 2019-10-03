#define MAX_ROOMS 10000

typedef struct RoomTable {
    RoomT *rooms[MAX_ROOMS];
} RoomTable;

RoomTable *create_room_table() {
    PGresult *res = fetch_all_rooms();
    RoomTable *room_table = hydrate_room_table(res);
    PQclear(res);
    return room_table;
}