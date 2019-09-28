#define MAX_EVENT_CONSUMERS 100

typedef struct {
    EventConsumer consumers[MAX_EVENT_CONSUMERS];
} EventDispatcher;

EventDispatcher *create_event_dispatcher() {
    return malloc(sizeof(EventDispatcher));
}