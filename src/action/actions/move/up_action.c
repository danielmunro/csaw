void do_up_action(GameServiceT *game_service, RequestT *request) {
    move_mob(
            get_location_table(game_service),
            request->mob,
            request->mob->room,
            UpDirection);
    do_look_action(game_service, request);
}

ActionT *create_up_action() {
    return create_action(Up, "up", do_up_action);
}
