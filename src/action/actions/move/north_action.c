void do_north_action(GameServiceT *game_service, Request *request) {
    move_mob(
            get_location_table(game_service),
            request->mob,
            request->mob->room,
            NorthDirection);
    do_look_action(game_service, request);
}

ActionT *create_north_action() {
    return create_action(North, "north", do_north_action);
}