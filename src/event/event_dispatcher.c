#define MAX_EVENT_CONSUMERS 100

typedef struct {
    EventConsumer *consumers[MAX_EVENT_CONSUMERS];
} EventDispatcher;

EventDispatcher *create_event_dispatcher() {
    return malloc(sizeof(EventDispatcher));
}

int ready_to_consume(EventConsumer *consumer, Event *event) {
    return consumer && event && consumer->event_type == event->type;
}

void dispatch_event(EventDispatcher *event_dispatcher, Event *event) {
    for (int i = 0; i < MAX_EVENT_CONSUMERS; i++) {
        if (ready_to_consume(event_dispatcher->consumers[i], event)) {
            event_dispatcher->consumers[i]->consume(event);
            if (event->status == Terminated) {
                return;
            }
        }
    }
}