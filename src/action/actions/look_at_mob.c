void do_look_at_mob_action(GameServiceT *game_service, Request *request) {
    char *buffer = room_to_string(request->mob->room, request->mob, get_location_table(game_service));
    ClientT *client = get_client_from_mob(game_service, request->mob);
    send_to_client(client, buffer);
    free(buffer);
}

ActionT *create_look_at_mob_action() {
    return create_action(LookAtMobAction, "look", create_words(2, ActionWord, MobInRoomWord), do_look_at_mob_action);
}