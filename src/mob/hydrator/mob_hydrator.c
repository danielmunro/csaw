Mob *hydrate_mob(PGresult *result, int row) {
    char * pEnd;
    uuid_t uuid;
    uuid_parse(PQgetvalue(result, row, 1), uuid);
    return create_mob(
            strtol(PQgetvalue(result, row, 0), &pEnd, 10),
            uuid,
            PQgetvalue(result, row, 2));
}

MobTable *hydrate_mob_table(PGresult *result) {
    int rows = PQntuples(result);
    MobTable *mobTable = malloc(sizeof(MobTable));
    for(int i = 0; i < rows; i++) {
        mobTable->mobs[i] = hydrate_mob(result, i);
    }
    return mobTable;
}
