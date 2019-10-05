void test_room_to_string() {
    // setup
    Room *room = create_room(0, uuid_from_string("640d7f58-5afe-4119-9da4-ce045451cfb7"), "test room");

    // when
    char *desc1 = room_to_string(room);
    char *desc2 = room_to_string(room);

    // then
    assert(strcmp(desc1, desc2) == 0);
}
