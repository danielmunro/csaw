void do_down_action(GameServiceT *game_service, RequestT *request) {
    do_move_action(game_service, request, DownDirection);
}

ActionT *create_down_action() {
    return create_action(Down, "down", do_down_action);
}
