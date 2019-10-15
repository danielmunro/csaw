#define MAX_MOBS 10000

typedef struct MobTable {
    Mob *mobs[MAX_MOBS];
} MobTable;

MobTable *create_mob_table() {
    PGresult *res = fetch_all_mobs();
    MobTable *mob_table = hydrate_mob_table(res);
    PQclear(res);
    return mob_table;
}

int count_mob_instances(MobTable *mob_table, Mob *mob) {
    int quantity = 0;
    for (int i = 0; i < MAX_MOBS; i++) {
        if (mob_table->mobs[i] &&
            mob_table->mobs[i]->canonical_id == mob->canonical_id) {
            quantity++;
        }
    }
    return quantity;
}
