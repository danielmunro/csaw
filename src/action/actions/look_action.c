char *room_to_string(Room *room) {

}

void do_look_action(GameServiceT *game_service, Request *request) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        ClientT *client = get_client(game_service, i);
        if (client) {
//            send_to_client(client, room_to_string());
        }
    }
}

ActionT *create_look_action() {
    return create_action(Look, "look", do_look_action);
}