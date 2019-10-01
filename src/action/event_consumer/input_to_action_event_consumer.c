void consume_input_to_action_event(GameServiceT *game_service, Event *event) {
    for (int i = 0; i < MAX_ACTIONS; i++) {
        if (game_service->action_table->actions[i] && strstr(game_service->action_table->actions[i]->name, event->buffer) == 0) {
            Event *action_event = create_action_event(game_service->action_table->actions[i]);
            dispatch_event(game_service, action_event);
            if (action_event->status == LiveEventStatus) {

            }
        }
    }
}

EventConsumer *create_input_to_action_event_consumer() {
    return create_event_consumer(InputEventType, consume_input_to_action_event);
}