void consume_test_input_event(Event *event) {
    event->buffer = "input";
}

void consume_and_terminate_test_input_event(Event *event) {
    event->buffer = "terminate";
    event->status = Terminated;
}

void consume_test_mob_moved_event(Event *event) {
    event->buffer = "mob_moved";
}

void test_dispatch_event_to_event_type() {
    // setup
    EventDispatcher *event_dispatcher = create_event_dispatcher();
    event_dispatcher->consumers[0] = create_event_consumer(Input, consume_test_input_event);
    event_dispatcher->consumers[1] = create_event_consumer(MobMoved, consume_test_mob_moved_event);

    // given
    Event *event = create_event(Input);

    // when
    dispatch_event(event_dispatcher, event);

    // then
    assert(event->buffer == "input");
}

void test_terminated_event_stops_consuming() {
    // setup
    EventDispatcher *event_dispatcher = create_event_dispatcher();
    event_dispatcher->consumers[0] = create_event_consumer(Input, consume_and_terminate_test_input_event);
    event_dispatcher->consumers[1] = create_event_consumer(Input, consume_test_input_event);
    event_dispatcher->consumers[2] = create_event_consumer(MobMoved, consume_test_mob_moved_event);

    // given
    Event *event = create_event(Input);

    // when
    dispatch_event(event_dispatcher, event);

    // then
    assert(event->buffer == "terminate");
    assert(event->status == Terminated);
}