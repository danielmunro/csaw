#ifdef MOCK
#define accept mock_accept
#define read mock_read
#endif
#define MAX_CLIENTS 100

int mocks[MAX_CLIENTS];

int mock_accept(int socket, struct sockaddr *addr, socklen_t *addrlen) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (!mocks[i]) {
            mocks[i] = i;
            return i;
        }
    }
    return -1;
}

int mock_read(int socket, char * buffer, int max_size) {
    buffer = "hello world";
    return strlen(buffer);
}