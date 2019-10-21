void test_look_describes_room() {
    // setup
    GameServiceT *g = create_game_service_with_test_area();
    Mob *mob = create_test_mob();
    char *out = room_to_string(g->room_table->rooms[0], mob, g->location_table);

    // given
    add_mob_location(g->location_table, mob, g->room_table->rooms[0]);

    // when
    do_look_action(g, create_request(LookAction, mob, "look"));

    // then
    MessageCollection *m = get_mock_message_collection();
    assert(strncmp(m->messages[0]->buffer, out, strlen(out)) == 0);
}

void test_mob_moves_north() {
    // setup
    GameServiceT *g = create_game_service_with_test_area();
    Mob *mob = create_test_mob();

    // given
    add_mob_location(g->location_table, mob, g->room_table->rooms[0]);

    // when
    do_north_action(g, create_request(NorthAction, mob, "north"));

    // then
    assert(mob->room == g->room_table->rooms[1]);
}

void test_mob_moves_south() {
    // setup
    GameServiceT *g = create_game_service_with_test_area();
    Mob *mob = create_test_mob();

    // given
    add_mob_location(g->location_table, mob, g->room_table->rooms[1]);

    // when
    do_south_action(g, create_request(NorthAction, mob, "south"));

    // then
    assert(mob->room == g->room_table->rooms[0]);
}

void test_mob_moves_east() {
    // setup
    GameServiceT *g = create_game_service_with_test_area();
    Mob *mob = create_test_mob();

    // given
    add_mob_location(g->location_table, mob, g->room_table->rooms[0]);

    // when
    do_east_action(g, create_request(EastAction, mob, "east"));

    // then
    assert(mob->room == g->room_table->rooms[2]);
}

void test_mob_moves_west() {
    // setup
    GameServiceT *g = create_game_service_with_test_area();
    Mob *mob = create_test_mob();

    // given
    add_mob_location(g->location_table, mob, g->room_table->rooms[2]);

    // when
    do_west_action(g, create_request(WestAction, mob, "west"));

    // then
    assert(mob->room == g->room_table->rooms[0]);
}

void test_mob_moves_up() {
    // setup
    GameServiceT *g = create_game_service_with_test_area();
    Mob *mob = create_test_mob();

    // given
    add_mob_location(g->location_table, mob, g->room_table->rooms[0]);

    // when
    do_up_action(g, create_request(UpAction, mob, "up"));

    // then
    assert(mob->room == g->room_table->rooms[3]);
}

void test_mob_moves_down() {
    // setup
    GameServiceT *g = create_game_service_with_test_area();
    Mob *mob = create_test_mob();

    // given
    add_mob_location(g->location_table, mob, g->room_table->rooms[3]);

    // when
    do_down_action(g, create_request(DownAction, mob, "down"));

    // then
    assert(mob->room == g->room_table->rooms[0]);
}

void test_invalid_move_does_nothing() {
    // setup
    GameServiceT *g = create_game_service();
    ClientT *c = create_client(g->server, TEST_SOCKET);
    c->mob = create_test_mob();
    create_test_area(g);

    // given
    add_mob_location(g->location_table, c->mob, g->room_table->rooms[0]);

    // when
    do_south_action(g, create_request(NorthAction, c->mob, "south"));

    // then
    assert(c->mob->room == g->room_table->rooms[0]);
}

void test_moving_sends_a_room_description_to_mob() {
    // setup
    GameServiceT *g = create_game_service();
    ClientT *c = create_client(g->server, TEST_SOCKET);
    c->mob = create_test_mob();
    create_test_area(g);

    // given
    add_mob_location(g->location_table, c->mob, g->room_table->rooms[0]);

    // when
    do_north_action(g, create_request(NorthAction, c->mob, "north"));

    // then
    MessageCollection *m = get_mock_message_collection();
    char *out = room_to_string(g->room_table->rooms[1], c->mob, g->location_table);
    assert(strncmp(m->messages[0]->buffer, out, strlen(out)) == 0);
}
