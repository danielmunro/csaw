void do_move_action(GameServiceT *game_service, RequestT *request, enum Direction direction) {
    move_mob(
            get_location_table(game_service),
            request->mob,
            request->mob->room,
            direction);
    do_look_action(game_service, request);
}
