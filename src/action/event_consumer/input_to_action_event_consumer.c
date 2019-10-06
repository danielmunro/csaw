void consume_input_to_action_event(GameServiceT *game_service, Event *event) {
    for (int i = 0; i < MAX_ACTIONS; i++) {
        ActionT *action = get_action(game_service, event->buffer);
        if (action) {
            Event *action_event = create_action_event(game_service->action_table->actions[i]);
            dispatch_event(game_service, action_event);
            if (action_event->status == LiveEventStatus) {
                Request *request = create_request(
                        action->action_type,
                        event->mob,
                        event->buffer);
                action->action(game_service, request);
                free(request);
            }
            free(action_event);
            return;
        }
    }
}

EventConsumer *create_input_to_action_event_consumer() {
    return create_event_consumer(InputEventType, consume_input_to_action_event);
}