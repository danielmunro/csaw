typedef struct {
    enum EventType event_type;
    void (*consumer)(Event *event);
} EventConsumer;

EventConsumer *create_event_consumer(enum EventType event_type, void (*consumer)(Event *event)) {
    EventConsumer *event_consumer = malloc(sizeof(EventConsumer));
    event_consumer->event_type = event_type;
    event_consumer->consumer = consumer;
    return event_consumer;
}