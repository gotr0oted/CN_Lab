/* Practical 2: TCP echo server (IPv4, port 8080). */
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

static int send_all(int fd, const char *data, size_t length) {
    size_t sent = 0;
    while (sent < length) {
        ssize_t n = send(fd, data + sent, length - sent, 0);
        if (n < 0 && errno == EINTR) continue;
        if (n <= 0) return -1;
        sent += (size_t)n;
    }
    return 0;
}

int main(void) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); return EXIT_FAILURE; }
    int reuse = 1;
    (void)setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind"); close(server_fd); return EXIT_FAILURE;
    }
    if (listen(server_fd, 5) < 0) {
        perror("listen"); close(server_fd); return EXIT_FAILURE;
    }
    printf("TCP echo server listening on port %d\n", PORT);

    for (;;) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            if (errno == EINTR) continue;
            perror("accept"); break;
        }
        puts("Client connected.");
        char buffer[BUFFER_SIZE];
        for (;;) {
            ssize_t n = recv(client_fd, buffer, sizeof(buffer), 0);
            if (n == 0) break;
            if (n < 0) {
                if (errno == EINTR) continue;
                perror("recv"); break;
            }
            if (send_all(client_fd, buffer, (size_t)n) < 0) { perror("send"); break; }
        }
        close(client_fd);
        puts("Client disconnected.");
    }
    close(server_fd);
    return EXIT_SUCCESS;
}
