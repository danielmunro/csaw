void test_client_can_look() {
    // setup
    GameServiceT *g = create_game_service();
    ClientT *c = create_client(g->server, TEST_SOCKET);
    c->mob = create_test_mob();
    create_test_area(g);
    char *out = room_to_string(g->room_table->rooms[0]);

    // given
    add_mob_location(g->location_table, c->mob, g->room_table->rooms[0]);

    // when
    do_look_action(g, create_request(Look, c->mob, "look"));

    // then
    MessageCollection *m = get_mock_message_collection();
    assert(strncmp(m->messages[0]->buffer, out, strlen(out)) == 0);
}
