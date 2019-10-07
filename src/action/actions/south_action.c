void do_south_action(GameServiceT *game_service, Request *request) {
    Room *room = request->mob->room;
    if (room) {
        for (int i = 0; i < MAX_EXITS; i++) {
            if (room->exits[i] && strcmp(room->exits[i]->direction, "south") == 0) {
                LocationTable *location_table = get_location_table(game_service);
                add_mob_location(location_table, request->mob, room->exits[i]->destination);
            }
        }
    }
}

ActionT *create_south_action() {
    return create_action(South, "south", do_south_action);
}