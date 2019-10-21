void do_say_action(GameServiceT *game_service, Request *request) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        ClientT *client = get_client(game_service, i);
        if (client) {
            client_send_to_clients(game_service, client, request->buffer);
        }
    }
}

ActionT *create_say_action() {
    return create_action(SayAction, "say", do_say_action);
}