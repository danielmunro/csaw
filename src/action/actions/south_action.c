void do_south_action(GameServiceT *game_service, Request *request) {

}

ActionT *create_south_action() {
    return create_action(South, "south", do_south_action);
}