#define MAX_INPUT 100

struct Client {
    struct sockaddr_in address;
    int socket;
    char * buffer[MAX_INPUT];
    int buffer_index;
    int delay;
};

ClientT *new_client(struct sockaddr_in address, int socket) {
    ClientT *c = malloc(sizeof(struct Client));
    c->address = address;
    c->socket = socket;
    c->buffer_index = 0;
    c->delay = 0;
    return c;
}

int get_buffer_index(ClientT *c) {
    if (c->buffer_index > MAX_INPUT - 1) {
        c->buffer_index = 0;
    }
    return c->buffer_index;
}

int add_buffer_to_client(ClientT *c, char * buffer) {
    int i = get_buffer_index(c);
    c->buffer[i] = buffer;
    return i;
}

char * get_next_buffer(ClientT *c) {
    int i = get_buffer_index(c);
    c->buffer_index++;
    return c->buffer[i];
}

int send_to_client(ClientT *c, char * message) {
    int bytes_sent = send(c->socket, message, strlen(message), 0);
    if (bytes_sent != strlen(message)) {
        perror("send");
    }
    return bytes_sent;
}
