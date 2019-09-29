#define MAX_REQUESTS 100

typedef struct {
    Action *actions[MAX_REQUESTS];
} ActionTable;

ActionTable *create_action_table() {
    ActionTable *a = malloc(sizeof(ActionTable));
    a->actions[0] = create_say_action();
    return a;
}