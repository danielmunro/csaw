typedef struct LocationTable {
    Mob *rooms[MAX_ROOMS][MAX_MOBS_PER_ROOM];
} LocationTable;

LocationTable *create_location_table() {
    return malloc(sizeof(LocationTable));
}
