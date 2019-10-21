void do_repeat_action(GameServiceT *game_service, Request *request) {
    ClientT *client = get_client_from_mob(game_service, request->mob);
    if (!client) {
        return;
    }
    EventT *event = create_client_input_event(client, request->buffer);
    dispatch_event(game_service, event);
    free(event);
}

ActionT *create_repeat_action() {
    return create_action(RepeatAction, "!", do_repeat_action);
}