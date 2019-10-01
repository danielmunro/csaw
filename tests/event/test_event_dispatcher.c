void consume_test_input_event(GameServiceT *game_service, Event *event) {
    event->buffer = "input";
}

void consume_and_terminate_test_input_event(GameServiceT *game_service, Event *event) {
    event->buffer = "terminate";
    event->status = TerminatedEventStatus;
}

void consume_test_mob_moved_event(GameServiceT *game_service, Event *event) {
    event->buffer = "mob_moved";
}

void test_dispatch_event_to_event_type() {
    // setup
    GameServiceT *game_service = create_game_service();
    game_service->event_dispatcher->consumers[0] = create_event_consumer(InputEventType, consume_test_input_event);
    game_service->event_dispatcher->consumers[1] = create_event_consumer(MobMovedEventType, consume_test_mob_moved_event);

    // given
    Event *event = create_event(InputEventType);

    // when
    dispatch_event(game_service, event);

    // then
    assert(event->buffer == "input");
}

void test_terminated_event_stops_consuming() {
    // setup
    GameServiceT *game_service = create_game_service();
    game_service->event_dispatcher->consumers[0] = create_event_consumer(InputEventType, consume_and_terminate_test_input_event);
    game_service->event_dispatcher->consumers[1] = create_event_consumer(InputEventType, consume_test_input_event);
    game_service->event_dispatcher->consumers[2] = create_event_consumer(MobMovedEventType, consume_test_mob_moved_event);

    // given
    Event *event = create_event(InputEventType);

    // when
    dispatch_event(game_service, event);

    // then
    assert(event->buffer == "terminate");
    assert(event->status == TerminatedEventStatus);
}