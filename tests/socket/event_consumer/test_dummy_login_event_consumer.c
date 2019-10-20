void test_dummy_login_adds_mob_to_start_room() {
    // setup
    GameServiceT *game_service = create_game_service();
    ClientT *client = create_client(game_service->server, 0);
    Room *room = create_test_room();
    room->id = START_ROOM_ID;
    game_service->room_table->rooms[0] = room;

    // given
    Event *event = create_login_event(client);

    // when
    dummy_login_event_consumer(game_service, event);

    // then
    assert(count_mob_instances(game_service->mob_table, event->mob) == 1);
    assert(get_mob_by_room_and_index(game_service->location_table, room, 0) != NULL);
}
