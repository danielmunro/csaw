typedef struct {
    Event *event;
    enum EventStatus status;
} ConsumedEvent;

ConsumedEvent *create_consumed_event(Event *event, enum EventStatus status) {
    ConsumedEvent *c = malloc(sizeof(ConsumedEvent));
    c->event = event;
    c->status = status;
    return c;
}