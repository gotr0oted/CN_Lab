/* Practical 3: TCP echo client for Practical 2. */
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

int main(int argc, char **argv) {
    const char *ip = argc > 1 ? argv[1] : "127.0.0.1";
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) { perror("socket"); return EXIT_FAILURE; }
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    if (inet_pton(AF_INET, ip, &server.sin_addr) != 1) {
        fprintf(stderr, "Enter a valid IPv4 address.\n"); close(fd); return EXIT_FAILURE;
    }
    if (connect(fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect"); close(fd); return EXIT_FAILURE;
    }
    char line[BUFFER_SIZE], response[BUFFER_SIZE];
    puts("Connected. Enter text; /quit closes the connection.");
    while (fgets(line, sizeof(line), stdin) != NULL) {
        if (strcmp(line, "/quit\n") == 0 || strcmp(line, "/quit") == 0) break;
        size_t length = strlen(line);
        if (send_all(fd, line, length) < 0) { perror("send"); break; }
        size_t received = 0;
        while (received < length) {
            ssize_t n = recv(fd, response + received, length - received, 0);
            if (n < 0 && errno == EINTR) continue;
            if (n <= 0) { fprintf(stderr, "Server closed the connection.\n"); goto done; }
            received += (size_t)n;
        }
        printf("Echo: %.*s", (int)received, response);
        if (response[received - 1] != '\n') putchar('\n');
    }
done:
    close(fd);
    return EXIT_SUCCESS;
}
