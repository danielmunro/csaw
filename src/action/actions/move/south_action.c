void do_south_action(GameServiceT *game_service, RequestT *request) {
    do_move_action(game_service, request, SouthDirection);
}

ActionT *create_south_action() {
    return create_action(South, "south", do_south_action);
}