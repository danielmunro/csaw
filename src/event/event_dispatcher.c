#define MAX_EVENT_CONSUMERS 100

typedef struct {
    EventConsumer *consumers[MAX_EVENT_CONSUMERS];
} EventDispatcher;

EventDispatcher *create_event_dispatcher() {
    return malloc(sizeof(EventDispatcher));
}

void dispatch_event(EventDispatcher *event_dispatcher, Event *event) {
    for (int i = 0; i < MAX_EVENT_CONSUMERS; i++) {
        if (event_dispatcher->consumers[i] && event_dispatcher->consumers[i]->event_type == event->event_type) {
            event_dispatcher->consumers[i]->consumer(event);
        }
    }
}