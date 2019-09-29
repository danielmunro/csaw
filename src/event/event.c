typedef struct {
    enum EventType event_type;
    Mob *mob;
    Client *client;
    char *buffer;
} Event;

Event *create_event(enum EventType event_type) {
    Event *event = malloc(sizeof(Event));
    event->event_type = event_type;
    return event;
}

Event *create_client_input_event(Client *client, char *buffer) {
    Event *event = create_event(Input);
    event->client = client;
    event->buffer = buffer;
    return event;
}