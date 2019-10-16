#include "header.h"

int DEBUG = 0;

void listen_csaw() {
    GameServiceT *game_service = create_game_service();
    open_main_socket(game_service->server);
    register_event_consumers(game_service->event_dispatcher);
    reset_mobs(game_service);
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