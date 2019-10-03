void test_get_action_sanity_1() {
    // setup
    GameServiceT *game_service = create_game_service();

    // when
    ActionT *action = get_action(game_service, "say");

    // then
    assert(action->action_type == Say);
}

void test_get_action_sanity_2() {
    // setup
    GameServiceT *game_service = create_game_service();

    // when
    ActionT *action = get_action(game_service, "sa");

    // then
    assert(action->action_type == Say);
}

void test_get_action_sanity_3() {
    // setup
    GameServiceT *game_service = create_game_service();

    // when
    ActionT *action = get_action(game_service, "s");

    // then
    assert(action->action_type == South);
}

void test_get_action_sanity_4() {
    // setup
    GameServiceT *game_service = create_game_service();

    // when
    ActionT *action = get_action(game_service, "floodle");

    // then
    assert(action == 0);
}

void test_client_can_send_a_message_to_other_clients() {
    // setup
    GameServiceT *game_service = create_game_service();
    ClientT *client1 = create_client(game_service->server, 0);
    ClientT *client2 = create_client(game_service->server, 1);
    ClientT *client3 = create_client(game_service->server, 2);
    char *buffer = "hello world";

    client_send_to_clients(game_service, client1, buffer);

//    MessageCollection *message_collection = get_mock_message_collection();
//    printf("hey %s\n", message_collection->messages[0]->buffer);
//    assert(message_collection->messages[0] != 0);
//    assert(message_collection->messages[0]->client == client2);
//    assert(message_collection->messages[0]->client == client2);
//    assert(message_collection->messages[0]->buffer == buffer);
//    assert(message_collection->messages[1]->client == client3);
//    assert(message_collection->messages[1]->buffer == buffer);
}