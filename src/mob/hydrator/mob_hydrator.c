Mob *hydrate_mob(PGresult *result, int row) {
    uuid_t uuid;
    uuid_parse(PQgetvalue(result, row, 1), uuid);
    return create_mob(
            int_from_result(result, row, 0),
            uuid,
            PQgetvalue(result, row, 2),
            PQgetvalue(result, row, 3));
}

MobTable *hydrate_mob_table(PGresult *result) {
    int rows = PQntuples(result);
    MobTable *mobTable = malloc(sizeof(MobTable));
    for(int i = 0; i < rows; i++) {
        mobTable->mobs[i] = hydrate_mob(result, i);
    }
    return mobTable;
}
