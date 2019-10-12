#define MAX_EVENT_CONSUMERS 100

typedef struct EventDispatcher {
    EventConsumerT *consumers[MAX_EVENT_CONSUMERS];
} EventDispatcher;

EventDispatcher *create_event_dispatcher() {
    EventDispatcher *event_dispatcher = malloc(sizeof(EventDispatcher));
    for (int i = 0; i < MAX_EVENT_CONSUMERS; i++) {
        event_dispatcher->consumers[i] = NULL;
    }
    return event_dispatcher;
}

int ready_to_consume(EventConsumerT *consumer, Event *event) {
    return consumer && event && consumer->event_type == event->event_type;
}
