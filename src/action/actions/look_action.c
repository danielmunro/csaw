void do_look_action(GameServiceT *game_service, Request *request) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        ClientT *client = get_client(game_service, i);
        if (client && client->mob == request->mob) {
            char buffer[1000] = "";
            room_to_string(client->mob->room, buffer);
            send_to_client(client, buffer);
            return;
        }
    }
}

ActionT *create_look_action() {
    return create_action(Look, "look", do_look_action);
}