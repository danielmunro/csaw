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
