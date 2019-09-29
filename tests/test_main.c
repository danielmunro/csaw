#define MOCK 1
#include "header.h"

int main() {
    // test_socket
    test_server_opens_main_socket();
    test_create_client_adds_client_to_server();
    test_new_connection_creates_client();
    test_end_client_session_removes_client_from_server();
    test_read_socket_adds_to_client_buffer();

    // test_client
    test_send_to_client_writes_data();

    // test_event_dispatcher
    test_dispatch_event_to_event_type();
}