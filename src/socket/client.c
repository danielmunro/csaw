#define MAX_INPUT 10
#define MAX_INPUT_LENGTH 1000

struct Client {
    struct sockaddr_in address;
    int socket;
    char *buffer[MAX_INPUT][MAX_INPUT_LENGTH];
    int index_write;
    int index_read;
    int delay;
    char *last_buffer;
    Mob *mob;
};

void reset_client_buffer(ClientT *client) {
    for (int i = 0; i < MAX_INPUT; i++) {
        memcpy(client->buffer[i], NULL, 0);
    }
    client->index_write = 0;
    client->index_read = 0;
}

ClientT *new_client(struct sockaddr_in address, int socket) {
    ClientT *c = malloc(sizeof(struct Client));
    c->address = address;
    c->socket = socket;
    c->delay = 0;
    reset_client_buffer(c);
    c->last_buffer = "";
    return c;
}

int add_buffer_to_client(ClientT *c, char *buffer) {
    int i = c->index_write;
    memset(c->buffer[i], 0, MAX_INPUT_LENGTH);
    memcpy(c->buffer[i], buffer, strlen(buffer) - 2);
    c->index_write++;
    return i;
}

char *get_next_buffer(ClientT *c) {
    if (c->index_write == 0) {
        return NULL;
    }
    if (c->index_write > c->index_read) {
        int i = c->index_read;
        char *buf = (char *) c->buffer[i];
        c->index_read++;
        return buf;
    }
    reset_client_buffer(c);
    return NULL;
}

char *get_next_input(ClientT *c) {
    char *buffer = get_next_buffer(c);
    if (buffer && strlen(buffer) > 0) {
        if (strcmp(buffer, "!") == 0) {
            return c->last_buffer;
        } else {
            c->last_buffer = malloc(strlen(buffer));
            strcpy(c->last_buffer, buffer);
            return buffer;
        }
    }
    return NULL;
}

int send_to_client(ClientT *c, char *buffer) {
    int bytes_sent = send(c->socket, buffer, strlen(buffer), 0);
    if (bytes_sent != strlen(buffer)) {
        perror("send");
    }
    return bytes_sent;
}
