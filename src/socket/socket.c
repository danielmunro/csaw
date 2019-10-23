#define PORT 8081
#define MAX_CLIENTS 100
#define MAX_READ_BUFFER 1024

char * welcome_message = "hello there";

typedef struct Server {
    fd_set reading_fds;
    int main_socket;
    ClientT *clients[MAX_CLIENTS];
    struct sockaddr_in address;
} Server;

Server *create_server() {
    Server *server = malloc(sizeof(Server));
    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->clients[i] = NULL;
    }
    return server;
}

typedef struct {
    ClientT *client;
    char * buffer;
} ClientBuffer;

ClientBuffer *create_client_buffer(ClientT *client, char * buffer) {
    ClientBuffer *c = malloc(sizeof(ClientBuffer));
    c->client = client;
    c->buffer = buffer;
    return c;
}

typedef struct {
    ClientBuffer *buffers[MAX_CLIENTS];
} ClientReadBuffers;

ClientReadBuffers *create_client_read_buffers() {
    ClientReadBuffers *rb = malloc(sizeof(ClientReadBuffers));
    for (int i = 0; i < MAX_CLIENTS; i++) {
        rb->buffers[i] = NULL;
    }
    return rb;
}

void open_main_socket(Server *s) {
    s->main_socket = socket(AF_INET, SOCK_STREAM, 0);
    int addrlen = sizeof(s->address);
    int opt = 1;

    if (s->main_socket == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(s->main_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    s->address.sin_family = AF_INET;
    s->address.sin_addr.s_addr = INADDR_ANY;
    s->address.sin_port = htons(PORT);

    if (bind(s->main_socket, (struct sockaddr *)&s->address, addrlen) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(s->main_socket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    puts("waiting for connections...");
}

ClientT *create_client(Server *s, int new_socket) {
    struct sockaddr_in address;
    getpeername(new_socket, (struct sockaddr*)&address, (socklen_t*)sizeof(address));
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if(!s->clients[i]) {
            s->clients[i] = new_client(address, new_socket);
            printf("Adding to list of sockets as %d\n" , i);
            return s->clients[i];
        }
    }
    return NULL;
}

ClientT *new_connection(Server *s) {
    int addrlen = sizeof(s->address);
    int new_socket = accept(s->main_socket, (struct sockaddr *)&s->address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("accept");
        return NULL;
    }
    printf("New connection, socket fd is %d, ip is : %s, port : %d\n",
           new_socket, inet_ntoa(s->address.sin_addr), ntohs(s->address.sin_port));
    ClientT *c = create_client(s, new_socket);
    send_to_client(c, welcome_message);
    return c;
}

void end_client_session(Server *s, ClientT *c) {
    struct sockaddr_in address;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (s->clients[i] == c) {
            free(s->clients[i]);
            s->clients[i] = 0;
            break;
        }
    }
    getpeername(c->socket, (struct sockaddr*)&address, (socklen_t*)sizeof(address));
    printf("Host disconnected, ip %s, port %d \n" ,
           inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
    close(c->socket);
}

void read_client_socket(Server *s, ClientT *client) {
    char raw_buffer[MAX_READ_BUFFER];
    char buffer[MAX_READ_BUFFER];
    int value = read(client->socket, raw_buffer, MAX_READ_BUFFER);
    if (value == 0) {
        end_client_session(s, client);
        return;
    }
    strncpy(buffer, raw_buffer, strlen(raw_buffer) - 1);
    debug_printf("READ from client socket: '%s', %d\n", buffer, value);
    add_buffer_to_client(client, buffer);
}

void check_clients(Server *s) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (s->clients[i] && FD_ISSET(s->clients[i]->socket, &s->reading_fds)) {
            read_client_socket(s, s->clients[i]);
        }
    }
}

void select_sockets(Server *s) {
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    select(MAX_CLIENTS, &s->reading_fds, NULL, NULL, &tv);
}



ClientReadBuffers *read_client_buffers(Server *s) {
    ClientReadBuffers *bufs = create_client_read_buffers();
    int read_buf_index = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (s->clients[i] && s->clients[i]->delay == 0) {
            char *next_input = get_next_input(s->clients[i]);
            if (next_input) {
                bufs->buffers[read_buf_index] = create_client_buffer(s->clients[i], next_input);
                read_buf_index++;
            }
        }
    }
    return bufs;
}

void loop_server(GameServiceT *game_service) {
    ServerT *s = get_server(game_service);
    FD_ZERO(&s->reading_fds);
    FD_SET(s->main_socket, &s->reading_fds);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (s->clients[i]) {
            FD_SET(s->clients[i]->socket, &s->reading_fds);
        }
    }
    select_sockets(s);
    if (FD_ISSET(s->main_socket, &s->reading_fds)) {
        ClientT *c = new_connection(s);
        if (!c) {
            perror("accept");
            exit(1);
        }
        EventT *event = create_login_event(c);
        dispatch_event(game_service, event);
        free(event);
    }
    check_clients(s);
}
