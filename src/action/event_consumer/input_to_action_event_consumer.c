void dispatch_action_event(GameServiceT *game_service, Event *event, ActionT *action) {
    Event *action_event = create_action_event(action);
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
}

void consume_input_to_action_event(GameServiceT *game_service, Event *event) {
    debug_printf(
            "input to action, mob: %s, event buffer: %s\n",
            event->mob->name,
            event->buffer);
    ActionT *action = get_action(game_service, event->buffer);
    if (action) {
        dispatch_action_event(game_service, event, action);
        return;
    }
}

EventConsumer *create_input_to_action_event_consumer() {
    return create_event_consumer(InputEventType, consume_input_to_action_event);
}