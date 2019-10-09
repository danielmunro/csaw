#define MOCK 1
#include "header.h"

int main() {
    void (*tests[MAX_TESTS])() = {
            test_room_to_string,
    };
    TestSuite *ts = create_test_suite(tests);
    run_tests(ts);
}