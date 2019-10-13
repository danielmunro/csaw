#define MAX_INPUT 100
#define MAX_INPUT_LENGTH 1000

struct Client {
    struct sockaddr_in address;
    int socket;
    char *buffer[MAX_INPUT][MAX_INPUT_LENGTH];
    int buffer_index;
    int delay;
    Mob *mob;
};

ClientT *new_client(struct sockaddr_in address, int socket) {
    ClientT *c = malloc(sizeof(struct Client));
    c->address = address;
    c->socket = socket;
    c->buffer_index = 0;
    c->delay = 0;
    return c;
}

void reset_client_buffer(ClientT *c) {
    for (int i = 0; i < MAX_INPUT; i++) {
        memcpy(c->buffer[i], "", 0);
    }
    c->buffer_index = 0;
}

int get_buffer_index(ClientT *c) {
    if (c->buffer_index > MAX_INPUT - 1) {
        c->buffer_index = 0;
    }
    return c->buffer_index;
}

int add_buffer_to_client(ClientT *c, char *buffer) {
    int i = get_buffer_index(c);
    memcpy(c->buffer[i], buffer, strlen(buffer) - 2);
    return i;
}

char *get_next_buffer(ClientT *c) {
    int i = get_buffer_index(c);
    c->buffer_index++;
    debug_printf("calling get_next_buffer with index: %d, new index: %d, buf: %s\n", i, c->buffer_index, c->buffer[i]);
    return (char *) c->buffer[i];
}

int send_to_client(ClientT *c, char *buffer) {
    int bytes_sent = send(c->socket, buffer, strlen(buffer), 0);
    if (bytes_sent != strlen(buffer)) {
        perror("send");
    }
    return bytes_sent;
}
