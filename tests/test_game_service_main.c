#define MOCK 1
#include "header.h"

int main() {
    void (*tests[MAX_TESTS])() = {
            test_dispatch_event_to_event_type,
            test_terminated_event_stops_consuming,
            test_get_action_sanity_1,
            test_get_action_sanity_2,
            test_get_action_sanity_3,
            test_get_action_sanity_4,
            test_client_can_send_a_message_to_other_clients,
    };
    TestSuite *ts = create_test_suite(tests);
    run_tests(ts);
}