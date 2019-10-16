#define MAX_MOBS 10000

typedef struct MobTable {
    Mob *mobs[MAX_MOBS];
} MobTable;

MobTable *create_mob_template_table() {
    PGresult *res = fetch_all_mobs();
    MobTable *mob_table = hydrate_mob_table(res);
    PQclear(res);
    return mob_table;
}

MobTable *create_mob_table() {
    MobTable *mob_table = malloc(sizeof(MobTable));
    for (int i = 0; i < MAX_MOBS; i++) {
        mob_table->mobs[i] = NULL;
    }
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

void add_to_mob_table(MobTable *mob_table, Mob *mob) {
    for (int i = 0; i < MAX_MOBS; i++) {
        if (!mob_table->mobs[i]) {
            mob_table->mobs[i] = mob;
            return;
        }
    }
    perror("mob table size");
}
