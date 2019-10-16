void reset_mobs_event_consumer(GameServiceT *game_service, Event *tick_event) {
    reset_mobs(game_service);
}

EventConsumer *create_reset_mobs_event_consumer() {
    return create_event_consumer(TickEventType, reset_mobs_event_consumer);
}