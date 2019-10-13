typedef struct TimeService {
    int seconds;
    int ticks;
    clock_t start;
} TimeService;

TimeService *create_time_service() {
    TimeService *ts = malloc(sizeof(TimeService));
    ts->start = clock();
    ts->seconds = 0;
    return ts;
}

int increment_time(TimeService *time_service) {
    debug_puts("increment_time");
    clock_t end = clock();
    double cpu_time_used = ((double) (end - time_service->start)) / CLOCKS_PER_SEC;
    int seconds = (int) cpu_time_used;
    if (seconds > 0) {
        time_service->seconds += seconds;
        time_service->start = end;
        debug_puts("SANITY");
    }
    return seconds;
}
