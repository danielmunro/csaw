#define MOCK 1
#include "header.h"

int main() {
    void (*tests[MAX_TESTS])() = {
            test_send_to_client_writes_data,
    };
    TestSuite *ts = create_test_suite(tests);
    run_tests(ts);
}