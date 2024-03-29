void test_room_to_string() {
    // setup
    uuid_t uuid;
    uuid_generate_random(uuid);
    Room *room = create_room(0, uuid, "test room");
    LocationTable *location_table = create_location_table();
    Mob *mob = create_test_mob();

    // when
    char *desc1 = room_to_string(room, mob, location_table);
    char *desc2 = room_to_string(room, mob, location_table);

    // then
    assert(strcmp(desc1, desc2) == 0);
}
