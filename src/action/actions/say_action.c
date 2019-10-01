void do_say_action(GameServiceT *game_service, Request *request) {

}

Action *create_say_action() {
    return create_action(Say, "say", do_say_action);
}