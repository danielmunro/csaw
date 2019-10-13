int int_from_result(PGresult *result, int row, int index) {
    char *pEnd;
    return strtol(PQgetvalue(result, row, index), &pEnd, 10);
}
