#include "header.h"

void listen_csaw() {
    GameService *game_service = create_game_service();
    open_main_socket(game_service->server);
    start_game_service(game_service);
}

int main() {
    PGconn *conn = create_db_connection();
    PGresult *res = fetch_all_mobs(conn);
//    MobTable *mobTable = hydrate_mob_table(res);
    PQclear(res);
    listen_csaw();
    PQfinish(conn);
    return 0;
}