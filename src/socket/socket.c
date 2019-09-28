#define PORT 8081
#define MAX_CLIENTS 100
#define MAX_READ_BUFFER 1024

char * welcome_message = "hello there";

typedef struct {
    fd_set reading_fds;
    int main_socket;
    Client *clients[MAX_CLIENTS];
    struct sockaddr_in address;
} Server;

Server *new_server() {
    return malloc(sizeof(Server));
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

Client *create_client(Server *s, int new_socket) {
    struct sockaddr_in address;
    getpeername(new_socket, (struct sockaddr*)&address, (socklen_t*)sizeof(address));
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if(!s->clients[i]) {
            s->clients[i] = new_client(address, new_socket);
            printf("Adding to list of sockets as %d\n" , i);
            return s->clients[i];
        }
    }
    return 0;
}

Client *new_connection(Server *s) {
    int addrlen = sizeof(s->address);
    int new_socket = accept(s->main_socket, (struct sockaddr *)&s->address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("accept");
        return 0;
    }
    printf("New connection, socket fd is %d, ip is : %s, port : %d\n",
           new_socket, inet_ntoa(s->address.sin_addr), ntohs(s->address.sin_port));
    Client *c = create_client(s, new_socket);
    send_to_client(c, welcome_message);
    return c;
}

void end_client_session(Server *s, Client *c) {
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

void read_client_socket(Server *s, Client *client) {
    char buffer[MAX_READ_BUFFER + 1];
    int value = read(client->socket, buffer, MAX_READ_BUFFER);
    if (value == 0) {
        end_client_session(s, client);
        return;
    }
    buffer[value] = '\0';
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
    select(MAX_CLIENTS, &s->reading_fds, NULL, NULL, NULL);
}

void read_client_buffers(Server *s) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (s->clients[i]) {
            char *buffer = get_next_buffer(s->clients[i]);
            if (buffer) {
                send(s->clients[i]->socket, buffer, strlen(buffer), 0);
            }
        }
    }
}

void loop_server(Server *s) {
    while (1) {
        FD_ZERO(&s->reading_fds);
        FD_SET(s->main_socket, &s->reading_fds);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (s->clients[i]) {
                int sd = s->clients[i]->socket;
                if (sd > 0) {
                    FD_SET(sd, &s->reading_fds);
                }
            }
        }
        select_sockets(s);
        if (FD_ISSET(s->main_socket, &s->reading_fds) && new_connection(s) < 0) {
            perror("accept");
            exit(1);
        }
        check_clients(s);
        read_client_buffers(s);
    }
}
