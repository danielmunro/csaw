void do_west_action(GameServiceT *game_service, RequestT *request) {
    do_move_action(game_service, request, WestDirection);
}

ActionT *create_west_action() {
    return create_action(WestAction, "west", do_west_action);
}