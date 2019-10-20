#define START_ROOM_ID 1431

void look_on_login(GameServiceT *game_service, Mob *mob) {
    RequestT *request = create_request(Look, mob, "look");
    do_look_action(game_service, request);
    free(request);
}

void dummy_login_event_consumer(GameServiceT *game_service, Event *event) {
    debug_printf("dummy login event consumer for client %d", event->client->socket);
    uuid_t uuid;
    uuid_generate_random(uuid);
    Mob *mob = create_mob(0, uuid,  create_object_description("dummy", "dummy", "dummy"), "canonical_id");
    event->client->mob = mob;
    event->mob = mob;
    Room *room = get_room(game_service->room_table, START_ROOM_ID);
    add_to_mob_table(game_service->mob_table, mob);
    add_mob_location(
            game_service->location_table,
            mob,
            room);
    look_on_login(game_service, mob);
}

EventConsumer *create_dummy_login_event_consumer() {
    return create_event_consumer(LoginEventType, dummy_login_event_consumer);
}