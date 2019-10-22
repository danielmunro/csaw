void test_get_action_sanity_1() {
    // setup
    GameServiceT *game_service = create_game_service();

    // when
    ActionT *action = get_action(game_service, "say\n");

    // then
    assert(action->action_type == SayAction);
}

void test_get_action_sanity_2() {
    // setup
    GameServiceT *game_service = create_game_service();

    // when
    ActionT *action = get_action(game_service, "sa\n");

    // then
    assert(action->action_type == SayAction);
}

void test_get_action_sanity_3() {
    // setup
    GameServiceT *game_service = create_game_service();

    // when
    ActionT *action = get_action(game_service, "s\n");

    // then
    assert(action->action_type == SouthAction);
}

void test_get_action_sanity_4() {
    // setup
    GameServiceT *game_service = create_game_service();

    // when
    ActionT *action = get_action(game_service, "floodle\n");

    // then
    assert(action == 0);
}

void test_look_at_mob_sanity() {
    // setup
    GameServiceT *game_service = create_game_service();

    // when
    ActionT *action = get_action(game_service, "look foo\n");

    // then
    assert(action->action_type == LookAtMobAction);
}

void test_client_can_send_a_message_to_other_clients() {
    // setup
    GameServiceT *game_service = create_game_service();
    ClientT *client1 = create_client(game_service->server, 0);
    ClientT *client2 = create_client(game_service->server, 1);
    ClientT *client3 = create_client(game_service->server, 2);

    // given
    char *buffer = "hello world";

    // when
    client_send_to_clients(game_service, client1, buffer);

    // then
    MessageCollection *message_collection = get_mock_message_collection();
    assert(message_collection->messages[0] != 0);
    assert(message_collection->messages[0]->client == client2);
    assert(message_collection->messages[0]->client == client2);
    assert(message_collection->messages[0]->buffer == buffer);
    assert(message_collection->messages[1]->client == client3);
    assert(message_collection->messages[1]->buffer == buffer);
}
