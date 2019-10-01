#define MAX_ACTIONS 100

typedef struct {
    ActionT *actions[MAX_ACTIONS];
} ActionTable;

ActionTable *create_action_table() {
    ActionTable *a = malloc(sizeof(ActionTable));
    a->actions[0] = create_say_action();
    return a;
}