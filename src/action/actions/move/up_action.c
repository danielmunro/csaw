void do_up_action(GameServiceT *game_service, RequestT *request) {
    do_move_action(game_service, request, UpDirection);
}

ActionT *create_up_action() {
    return create_action(Up, "up", do_up_action);
}
