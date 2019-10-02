PGresult *fetch_all_mobs() {
    PGresult *res = PQexec(conn, query_all_mobs);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("No data retrieved\n");
        PQclear(res);
        close_db_conneciton();
    }

    return res;
}
