void do_east_action(GameServiceT *game_service, RequestT *request) {
    move_mob(
            get_location_table(game_service),
            request->mob,
            request->mob->room,
            EastDirection);
    do_look_action(game_service, request);
}

ActionT *create_east_action() {
    return create_action(East, "east", do_east_action);
}
