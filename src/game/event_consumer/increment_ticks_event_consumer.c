void increment_ticks_event_consumer(GameServiceT *game_service, Event *tick_event) {
    game_service->time_service->ticks++;
    debug_printf("tick %d\n", game_service->time_service->ticks);
}

EventConsumer *create_increment_ticks_event_consumer() {
    return create_event_consumer(TickEventType, increment_ticks_event_consumer);
}