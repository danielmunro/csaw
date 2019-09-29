int result = 0;

void consume_test_input_event(Event *event) {
    result = 1;
}

void consume_test_mob_moved_event(Event *event) {
    result = 2;
}

void test_dispatch_event_to_event_type() {
    EventDispatcher *event_dispatcher = create_event_dispatcher();
    event_dispatcher->consumers[0] = create_event_consumer(Input, consume_test_input_event);
    event_dispatcher->consumers[1] = create_event_consumer(MobMoved, consume_test_mob_moved_event);

    dispatch_event(event_dispatcher, create_event(Input));

    assert(result == 1);
}