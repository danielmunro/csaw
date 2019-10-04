char *room_to_string(Room *room) {
    char *buffer = strcpy(room->name, "\nExits [");
    for (int i = 0; i < MAX_EXITS; i++) {
        if (room->exits[i]) {
            buffer = strcpy(buffer, &room->exits[i]->direction[0]);
        }
    }
    return strcpy(buffer, "]");
}

void do_look_action(GameServiceT *game_service, Request *request) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        ClientT *client = get_client(game_service, i);
        if (client) {
            send_to_client(client, room_to_string(request->mob->room));
        }
    }
}

ActionT *create_look_action() {
    return create_action(Look, "look", do_look_action);
}