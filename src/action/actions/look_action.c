void room_to_string(Room *room, char *out) {
    char buffer[1000] = "";
    strcat(out, room->name);
    strcat(out, "\nExits [");
    for (int j = 0; j < MAX_EXITS - 1; j++) {
        if (room->exits[j]) {
            strncat(buffer, room->exits[j]->direction, 1);
        }
    }
    strcat(out, "]");
}

void do_look_action(GameServiceT *game_service, Request *request) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        ClientT *client = get_client(game_service, i);
        if (client && client->mob == request->mob) {
            char buffer[1000] = "";
            strcat(buffer, client->mob->room->name);
            strcat(buffer, "\nExits [");
            for (int j = 0; j < MAX_EXITS - 1; j++) {
                if (client->mob->room->exits[j]) {
                    strncat(buffer, client->mob->room->exits[j]->direction, 1);
                }
            }
            strcat(buffer, "]");
            send_to_client(client, buffer);
            return;
        }
    }
}

ActionT *create_look_action() {
    return create_action(Look, "look", do_look_action);
}