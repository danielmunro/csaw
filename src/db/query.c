PGresult *fetch_all_mobs(PGconn *conn) {
    PGresult *res = PQexec(conn, query_all_mobs);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("No data retrieved\n");
        PQclear(res);
        do_exit(conn);
    }

    return res;
}
