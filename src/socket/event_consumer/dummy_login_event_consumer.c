void dummy_login_event_consumer(GameServiceT *game_service, Event *event) {
    debug_puts("dummy login event consumer");
    uuid_t uuid;
    uuid_generate_random(uuid);
    event->client->mob = create_mob(0, uuid,  "dummy");
    Room *room = get_room(game_service->room_table, 1431);
    add_mob_location(
            game_service->location_table,
            event->client->mob,
            room);
//    RequestT *request = create_request(Look, event->mob, "look");
//    do_look_action(game_service, request);
//    free(request);
}

EventConsumer *create_dummy_login_event_consumer() {
    return create_event_consumer(LoginEventType, dummy_login_event_consumer);
}