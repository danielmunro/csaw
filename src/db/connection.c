PGconn *conn;

void close_db_conneciton() {
    PQfinish(conn);
}

PGconn *create_db_connection() {
    conn = PQconnectdb("host=localhost user=postgres dbname=nodesrv password=nodesrv");
    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n",
                PQerrorMessage(conn));
        close_db_conneciton();
        exit(1);
    }
    return conn;
}