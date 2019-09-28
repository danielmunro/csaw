#ifdef MOCK
#define send mock_send
#endif

int mock_send(int socket, char * message, int message_length, int timeout) {
    return strlen(message);
}