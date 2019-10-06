void test_client_can_look() {
    // setup
    GameServiceT *g = create_game_service();
    ClientT *c = create_client(g->server, TEST_SOCKET);
    c->mob = create_test_mob();
    uuid_t uuid1;
    uuid_generate_random(uuid1);
    Room *room1 = create_room(0, uuid1, "test room");
    uuid_t uuid2;
    uuid_generate_random(uuid1);
    Room *room2 = create_room(1, uuid2, "test room");
    room1->exits[0] = create_exit(0, room1, room2, "north");
    g->room_table->rooms[0] = room1;
    add_mob_location(g, c->mob, room1);
    MessageCollection *m = get_mock_message_collection();
    char *out = room_to_string(room1);

    // when
    do_look_action(g, create_request(Look, c->mob, "look"));

    // then
    assert(strncmp(m->messages[0]->buffer, out, strlen(out)) == 0);
}
