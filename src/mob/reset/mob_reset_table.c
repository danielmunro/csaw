#define MAX_MOB_RESETS 10000

typedef struct MobResetTable {
    MobReset *resets[MAX_MOB_RESETS];
} MobResetTable;

MobResetTable *create_mob_reset_table(GameServiceT *game_service) {
    PGresult *result = fetch_all_mob_resets();
    return hydrate_mob_reset_table(game_service, result);
}
