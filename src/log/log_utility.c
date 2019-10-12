void debug_printf(char *fmt, ...) {
    if (!DEBUG) {
        return;
    }
    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
}

void debug_puts(char *out) {
    if (!DEBUG) {
        return;
    }
    puts(out);
}