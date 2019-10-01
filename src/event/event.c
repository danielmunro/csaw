typedef struct {
    enum EventType event_type;
    enum EventStatus status;
    Action *action;
    Mob *mob;
    Client *client;
    char *buffer;
} Event;

Event *create_event(enum EventType event_type) {
    Event *event = malloc(sizeof(Event));
    event->event_type = event_type;
    event->status = LiveEventStatus;
    return event;
}

Event *create_client_input_event(Client *client, char *buffer) {
    Event *event = create_event(InputEventType);
    event->client = client;
    event->buffer = buffer;
    return event;
}

Event *create_action_event(Action *action) {
    Event *event = create_event(ActionEventType);
    event->action = action;
    return event;
}