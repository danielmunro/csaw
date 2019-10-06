void test_room_to_string() {
    // setup
    uuid_t uuid;
    uuid_generate_random(uuid);
    Room *room = create_room(0, uuid, "test room");

    // when
    char *desc1 = room_to_string(room);
    char *desc2 = room_to_string(room);

    // then
    assert(strcmp(desc1, desc2) == 0);
}
