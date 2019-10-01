#define MAX_EVENT_CONSUMERS 100

typedef struct {
    EventConsumer *consumers[MAX_EVENT_CONSUMERS];
} EventDispatcher;

EventDispatcher *create_event_dispatcher() {
    return malloc(sizeof(EventDispatcher));
}

int ready_to_consume(EventConsumer *consumer, Event *event) {
    return consumer && event && consumer->event_type == event->event_type;
}
