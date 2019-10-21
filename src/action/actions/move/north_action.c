void do_north_action(GameServiceT *game_service, Request *request) {
    do_move_action(game_service, request, NorthDirection);
}

ActionT *create_north_action() {
    return create_action(North, "north", do_north_action);
}