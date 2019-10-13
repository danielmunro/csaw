#define TICK_DURATION_IN_SECONDS 5

void consume_pulse_event_for_ticks(GameServiceT *game_service, Event *pulse_event) {
    if (game_service->time_service->seconds > TICK_DURATION_IN_SECONDS) {
        game_service->time_service->seconds = 0;
        game_service->time_service->ticks++;
        debug_printf("tick %d\n", game_service->time_service->ticks);
        Event *tick_event = create_tick_event();
        dispatch_event(game_service, tick_event);
        free(tick_event);
    }
}

EventConsumer *create_pulse_to_tick_event_consumer() {
    return create_event_consumer(PulseEventType, consume_pulse_event_for_ticks);
}