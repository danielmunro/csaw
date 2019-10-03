#define MOCK 1
#include "header.h"

int main() {
    // test_event_dispatcher
    test_dispatch_event_to_event_type();
    test_terminated_event_stops_consuming();

    // test_game_service
    test_get_action_sanity_1();
    test_get_action_sanity_2();
    test_get_action_sanity_3();
    test_get_action_sanity_4();
    test_client_can_send_a_message_to_other_clients();
}