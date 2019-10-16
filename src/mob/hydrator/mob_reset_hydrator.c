MobReset *hydrate_mob_reset(GameServiceT *game_service, PGresult *result, int row) {
    int mob_id = int_from_result(result, row, 1);
    int room_id = int_from_result(result, row, 2);
    int max_quantity = int_from_result(result, row, 3);
    int max_per_room = int_from_result(result, row, 4);
    Mob *mob = get_mob_template_by_id(game_service, mob_id);
    RoomT *room = get_room_by_id(game_service, room_id);
    if (!mob || !room) {
        if (!mob) {
            debug_puts("NO MOB");
        }
        if (!room) {
            debug_puts("NO ROOM");
        }
        perror("reset");
        return NULL;
    }
    return create_mob_reset(
            int_from_result(result, row, 0),
            mob,
            room,
            max_quantity,
            max_per_room);
}

MobResetTable *hydrate_mob_reset_table(GameServiceT *game_service, MobResetTable *table, PGresult *result) {
    int rows = PQntuples(result);
    int index = 0;
    for(int i = 0; i < rows; i++) {
        MobReset *reset = hydrate_mob_reset(game_service, result, i);
        if (reset) {
            table->resets[index] = reset;
            index++;
        }
    }
    return table;
}
