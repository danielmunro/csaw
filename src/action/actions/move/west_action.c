void do_west_action(GameServiceT *game_service, RequestT *request) {
    move_mob(
            get_location_table(game_service),
            request->mob,
            request->mob->room,
            WestDirection);
    do_look_action(game_service, request);
}

ActionT *create_west_action() {
    return create_action(West, "west", do_west_action);
}