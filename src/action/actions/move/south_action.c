void do_south_action(GameServiceT *game_service, Request *request) {
    move_mob(
            get_location_table(game_service),
            request->mob,
            request->mob->room,
            SouthDirection);
}

ActionT *create_south_action() {
    return create_action(South, "south", do_south_action);
}