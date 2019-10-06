int mob_fixture_id = 0;

Mob *create_test_mob() {
    uuid_t uuid;
    uuid_generate_random(uuid);
    Mob *mob = create_mob(
            mob_fixture_id,
            uuid,
            "test mob");
    mob_fixture_id++;
    return mob;
}