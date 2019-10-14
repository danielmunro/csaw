#define TICK_DURATION_IN_SECONDS 30

void consume_pulse_event_for_ticks(GameServiceT *game_service, Event *pulse_event) {
    if (game_service->time_service->seconds > TICK_DURATION_IN_SECONDS) {
        game_service->time_service->seconds = 0;
        Event *tick_event = create_tick_event();
        dispatch_event(game_service, tick_event);
        free(tick_event);
    }
}

EventConsumer *create_pulse_to_tick_event_consumer() {
    return create_event_consumer(PulseEventType, consume_pulse_event_for_ticks);
}