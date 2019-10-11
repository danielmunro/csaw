void dispatch_action_event(GameServiceT *game_service, Event *event, ActionT *action) {
    puts("start dispatch action event");
    Event *action_event = create_action_event(action);
    dispatch_event(game_service, action_event);
    puts("after action event dispatch");
    if (action_event->status == LiveEventStatus) {
        puts("sanity 1");
        Request *request = create_request(
                action->action_type,
                event->mob,
                event->buffer);
        printf("request created for action %s\n", action->name);
        action->action(game_service, request);
        puts("sanity 2");
        free(request);
    }
    free(action_event);
    puts("done dispatch action event");
}

void consume_input_to_action_event(GameServiceT *game_service, Event *event) {
    printf("consume_input_to_action_event, event buffer: %s\n", event->buffer);
    ActionT *action = get_action(game_service, event->buffer);
    if (action != NULL) {
        puts("action is not null");
        printf("action being invoked, %s\n", action->name);
        dispatch_action_event(game_service, event, action);
        return;
    }
    puts("nothing for input to action_event to do");
}

EventConsumer *create_input_to_action_event_consumer() {
    return create_event_consumer(InputEventType, consume_input_to_action_event);
}