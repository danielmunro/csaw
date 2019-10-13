typedef struct Event {
    enum EventType event_type;
    enum EventStatus status;
    ActionT *action;
    Mob *mob;
    ClientT *client;
    char *buffer;
} Event;

Event *create_event(enum EventType event_type) {
    Event *event = malloc(sizeof(Event));
    event->event_type = event_type;
    event->status = LiveEventStatus;
    return event;
}

Event *create_client_input_event(ClientT *client, char *buffer) {
    Event *event = create_event(InputEventType);
    event->client = client;
    event->mob = client->mob;
    event->buffer = buffer;
    return event;
}

Event *create_action_event(ActionT *action) {
    Event *event = create_event(ActionEventType);
    event->action = action;
    return event;
}

EventT *create_login_event(ClientT *client) {
    Event *event = create_event(LoginEventType);
    event->client = client;
    event->mob = client->mob;
    return event;
}

EventT *create_pulse_event() {
    Event *event = create_event(PulseEventType);
    return event;
}

EventT *create_tick_event() {
    Event *event = create_event(TickEventType);
    return event;
}
