#include "header.h"

int DEBUG = 0;

void listen_csaw() {
    GameServiceT *game_service = create_game_service();
    open_main_socket(game_service->server);
    game_service->event_dispatcher->consumers[0] = create_echo_event_consumer();
    game_service->event_dispatcher->consumers[1] = create_input_to_action_event_consumer();
    game_service->event_dispatcher->consumers[2] = create_dummy_login_event_consumer();
    start_game_service(game_service);
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "DEBUG") == 0) {
            DEBUG = 1;
        }
    }
    create_db_connection();
    listen_csaw();
    close_db_conneciton();
    return 0;
}