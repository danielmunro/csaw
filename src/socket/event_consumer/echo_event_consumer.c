void consume_echo_event(GameServiceT *game_service, Event *event) {
    send(event->client->socket, event->buffer, strlen(event->buffer), 0);
}

EventConsumer *create_echo_event_consumer() {
    return create_event_consumer(InputEventType, consume_echo_event);
}