#define MAX_MOB_RESETS 10000

typedef struct MobResetTable {
    MobReset *resets[MAX_MOB_RESETS];
} MobResetTable;

MobResetTable *create_mob_reset_table() {
    MobResetTable *table = malloc(sizeof(MobResetTable));
    for (int i = 0; i < MAX_MOB_RESETS; i++) {
        table->resets[i] = NULL;
    }
    return table;
}

MobResetTable *create_hydrated_mob_reset_table(GameServiceT *game_service) {
    PGresult *result = fetch_all_mob_resets();
    return hydrate_mob_reset_table(game_service, create_mob_reset_table(), result);
}

void do_mob_reset(GameServiceT *game_service, MobResetT *reset) {
    int max_quantity = reset->max_quantity;
    int max_per_room = reset->max_per_room;
    MobTable *mob_table = get_mob_table(game_service);
    LocationTableT *location_table = get_location_table(game_service);
    int quantity = count_mob_instances(mob_table, reset->mob);
    int in_room = count_mobs_in_room_by_mob(location_table, reset->room, reset->mob);
    int quantity_diff = max_quantity - quantity;
    int in_room_diff = max_per_room - in_room;
    if (quantity_diff <= 0 || in_room_diff <= 0) {
        return;
    }
    int num_to_create = quantity_diff < in_room_diff ? quantity_diff : in_room_diff;
    debug_printf("creating %d instance(s) of %s\n", num_to_create, reset->mob->name);
    for (int i = 0; i < num_to_create; i++) {
        Mob *mob = create_mob(
                reset->mob->id,
                reset->mob->uuid,
                reset->mob->name,
                reset->mob->canonical_id);
        add_to_mob_table(mob_table, mob);
        add_mob_location(location_table, mob, reset->room);
    }
}
