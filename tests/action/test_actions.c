void test_client_can_look() {
    // setup
    GameServiceT *g = create_game_service();
    ClientT *c = create_client(g->server, TEST_SOCKET);
    c->mob = create_test_mob();
    Room *room1 = create_test_room();
    Room *room2 = create_test_room();
    room1->exits[0] = create_exit(0, room1, room2, get_direction_from_string("north"));
    g->room_table->rooms[0] = room1;
    g->room_table->rooms[1] = room2;
    char *out = room_to_string(room1);

    // given
    add_mob_location(g->location_table, c->mob, room1);

    // when
    do_look_action(g, create_request(Look, c->mob, "look"));

    // then
    MessageCollection *m = get_mock_message_collection();
    assert(strncmp(m->messages[0]->buffer, out, strlen(out)) == 0);
}
