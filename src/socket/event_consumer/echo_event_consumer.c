void consume_echo_event(Event *event) {
    send(event->client->socket, event->buffer, strlen(event->buffer), 0);
}

EventConsumer *create_echo_event_consumer() {
    return create_event_consumer(Input, consume_echo_event);
}