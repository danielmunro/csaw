#include <libpq-fe.h>

void do_exit(PGconn *conn) {
    PQfinish(conn);
    exit(1);
}

PGconn *create_db_connection() {
    PGconn *conn = PQconnectdb("host=localhost user=postgres dbname=nodesrv password=nodesrv");
    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n",
                PQerrorMessage(conn));
        do_exit(conn);
    }
    return conn;
}