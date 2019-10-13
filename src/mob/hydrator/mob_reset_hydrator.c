MobReset *hydrate_mob_reset(GameServiceT *game_service, PGresult *result, int row) {
    int mob_id = int_from_result(result, row, 1);
    int room_id = int_from_result(result, row, 2);
    int max_quantity = int_from_result(result, row, 3);
    int max_per_room = int_from_result(result, row, 4);
    return create_mob_reset(
            int_from_result(result, row, 0),
            get_mob_by_id(game_service, mob_id),
            get_room_by_id(game_service, room_id),
            max_quantity,
            max_per_room);
}

MobResetTable *hydrate_mob_reset_table(GameServiceT *game_service, PGresult *result) {
    int rows = PQntuples(result);
    MobResetTable *table = malloc(sizeof(MobResetTable));
    for(int i = 0; i < rows; i++) {
        table->resets[i] = hydrate_mob_reset(game_service, result, i);
    }
    return table;
}
