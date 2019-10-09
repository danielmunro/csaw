#define MOCK 1
#include "header.h"

int main() {
    void (*tests[MAX_TESTS])() = {
            test_look_describes_room,
            test_mob_moves_north,
            test_mob_moves_south,
            test_invalid_move_does_nothing,
            test_moving_sends_a_room_description_to_mob,
    };
    TestSuite *ts = create_test_suite(tests);
    run_tests(ts);
}