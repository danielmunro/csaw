#ifdef MOCK
#define send mock_send
#define send_to_client mock_send_to_client
#endif
#define MAX_SENT_MESSAGES 100

int mock_send(int socket, char * message, int message_length, int timeout) {
    return strlen(message);
}

typedef struct SentMessage {
    ClientT *client;
    char *buffer;
} SentMessage;

SentMessage *create_sent_message(ClientT *client, char *buffer) {
    SentMessage *s = malloc(sizeof(SentMessage));
    s->client = client;
    s->buffer = buffer;
    return s;
}

typedef struct MessageCollection {
    SentMessage *messages[MAX_SENT_MESSAGES];
} MessageCollection;

MessageCollection *_m;
int m_index = 0;
int initialized = 0;

MessageCollection *get_mock_message_collection() {
    if (initialized == 0) {
        _m = malloc(sizeof(MessageCollection));
        initialized = 1;
    }
    return _m;
}

int mock_send_to_client(ClientT *c, char *buffer) {
    MessageCollection *message_collection = get_mock_message_collection();
    message_collection->messages[m_index] = create_sent_message(c, buffer);
    m_index++;
    return strlen(buffer);
}
