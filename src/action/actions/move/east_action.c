void do_east_action(GameServiceT *game_service, RequestT *request) {
    do_move_action(game_service, request, EastDirection);
}

ActionT *create_east_action() {
    return create_action(EastAction, "east", create_single_word(), do_east_action);
}
