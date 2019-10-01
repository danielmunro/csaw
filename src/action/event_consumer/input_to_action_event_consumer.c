void consume_input_to_action_event(Event *event) {
}

EventConsumer *create_input_to_action_event_consumer() {
    return create_event_consumer(Input, consume_input_to_action_event);
}