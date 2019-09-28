void test_send_to_client_writes_data() {
    // setup
    Server *s = new_server();
    Client *c = new_connection(s);

    // given
    char * message = "hello world";

    // when
    int bytes_sent = send_to_client(c, message);

    // then
    assert(bytes_sent == strlen(message));
}