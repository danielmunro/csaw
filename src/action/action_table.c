#define MAX_ACTIONS 100

typedef struct {
    ActionT *actions[MAX_ACTIONS];
} ActionTable;

ActionTable *create_action_table() {
    ActionTable *a = malloc(sizeof(ActionTable));
    for(int i = 0; i < MAX_ACTIONS; i++) {
        a->actions[i] = NULL;
    }

    // movement
    a->actions[0] = create_south_action();
    a->actions[1] = create_north_action();
    a->actions[2] = create_east_action();
    a->actions[3] = create_west_action();
    a->actions[4] = create_up_action();
    a->actions[5] = create_down_action();

    a->actions[10] = create_say_action();
    a->actions[20] = create_look_action();
    a->actions[21] = create_look_at_mob_action();
    a->actions[30] = create_repeat_action();
    return a;
}