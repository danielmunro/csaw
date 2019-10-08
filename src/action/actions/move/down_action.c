void do_down_action(GameServiceT *game_service, RequestT *request) {
    move_mob(
            get_location_table(game_service),
            request->mob,
            request->mob->room,
            DownDirection);
    do_look_action(game_service, request);
}

ActionT *create_down_action() {
    return create_action(Down, "down", do_down_action);
}
