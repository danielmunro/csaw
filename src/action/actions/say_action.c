void do_say_action(GameServiceT *game_service, Request *request) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        ClientT *client = get_client(game_service, i);
        if (client) {
            send(client->socket, request->buffer, strlen(request->buffer), 0);
        }
    }
}

ActionT *create_say_action() {
    return create_action(Say, "say", do_say_action);
}