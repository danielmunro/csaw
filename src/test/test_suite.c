#define MAX_TESTS 100

typedef struct {
    void (*tests[MAX_TESTS])();
} TestSuite;

TestSuite *create_test_suite(void (*tests[MAX_TESTS])()) {
    TestSuite *t = malloc(sizeof(TestSuite));
    memcpy(t->tests, tests, MAX_TESTS);
    return t;
}

void run_tests(TestSuite *ts) {
    for (int i = 0; i < MAX_TESTS; i++) {
        if(ts->tests[i]) {
            clear_mock_message_collection();
            ts->tests[i]();
        }
    }
}
