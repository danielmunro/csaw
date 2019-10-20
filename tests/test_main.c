#define MOCK 1
#include "header.h"

void run_action_tests() {
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

void run_client_tests() {
    void (*tests[MAX_TESTS])() = {
            test_send_to_client_writes_data,
    };
    TestSuite *ts = create_test_suite(tests);
    run_tests(ts);
}

void run_game_service_tests() {
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

void run_room_tests() {
    void (*tests[MAX_TESTS])() = {
            test_room_to_string,
            test_direction_enum_sanity_checks,
            test_direction_string_sanity_checks,
    };
    TestSuite *ts = create_test_suite(tests);
    run_tests(ts);
}

void run_socket_tests() {
    void (*tests[MAX_TESTS])() = {
            test_server_opens_main_socket,
            test_create_client_adds_client_to_server,
            test_new_connection_creates_client,
            test_end_client_session_removes_client_from_server,
            test_read_socket_adds_to_client_buffer,
            test_dummy_login_adds_mob_to_start_room,
    };
    TestSuite *ts = create_test_suite(tests);
    run_tests(ts);
}

int main() {
    run_action_tests();
    run_client_tests();
    run_game_service_tests();
    run_room_tests();
    run_socket_tests();
}