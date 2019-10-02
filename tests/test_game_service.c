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
