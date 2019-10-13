typedef struct MobReset {
    int id;
    Mob *mob;
    RoomT *room;
    int max_quantity;
    int max_per_room;
} MobReset;

MobReset *create_mob_reset(int id, Mob *mob, RoomT *room, int max_quantity, int max_per_room) {
    MobReset *mob_reset = malloc(sizeof(MobReset));
    mob_reset->id = id;
    mob_reset->mob = mob;
    mob_reset->room = room;
    mob_reset->max_quantity = max_quantity;
    mob_reset->max_per_room = max_per_room;
    return mob_reset;
}