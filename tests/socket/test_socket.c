#define TEST_SOCKET 1

void test_server_opens_main_socket() {
    // given
    Server *s = create_server();

    // when
    open_main_socket(s);

    // then
    assert(s->main_socket > 0);
}

void test_create_client_adds_client_to_server() {
    // given
    Server *s = create_server();

    // when
    ClientT *c = create_client(s, TEST_SOCKET);

    // then
    assert(c != NULL);
}

void test_new_connection_creates_client() {
    // given
    Server *s = create_server();

    // when
    ClientT *c = new_connection(s);

    // then
    assert(c != NULL);
}

void test_end_client_session_removes_client_from_server() {
    // setup
    Server *s = create_server();
    ClientT *c = new_connection(s);

    // when
    end_client_session(s, c);

    // then
    for (int i = 0; i < MAX_CLIENTS; i++) {
        assert(s->clients[i] == 0);
    }
}

void test_read_socket_adds_to_client_buffer() {
    // setup
    Server *s = create_server();
    ClientT *c = new_connection(s);

    // when
    read_client_socket(s, c);

    // then
    assert(s->clients[0]->buffer[0] != NULL);
}
