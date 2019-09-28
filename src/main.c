#include "header.h"

void listen_csaw() {
    Server *server = new_server();
    open_main_socket(server);
    loop_server(server);
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