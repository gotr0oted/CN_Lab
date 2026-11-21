/* Practical 4: UDP echo client for Practical 5. */
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv) {
    const char *ip = argc > 1 ? argv[1] : "127.0.0.1";
    long port = argc > 2 ? strtol(argv[2], NULL, 10) : 9090;
    if (port < 1 || port > 65535) { fprintf(stderr, "Invalid port.\n"); return EXIT_FAILURE; }
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) { perror("socket"); return EXIT_FAILURE; }
    struct timeval timeout = {5, 0};
    (void)setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons((unsigned short)port);
    if (inet_pton(AF_INET, ip, &server.sin_addr) != 1) {
        fprintf(stderr, "Enter a valid IPv4 address.\n"); close(fd); return EXIT_FAILURE;
    }
    char message[BUFFER_SIZE];
    fputs("Message: ", stdout);
    if (fgets(message, sizeof(message), stdin) == NULL) { close(fd); return EXIT_SUCCESS; }
    size_t length = strlen(message);
    if (sendto(fd, message, length, 0, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("sendto"); close(fd); return EXIT_FAILURE;
    }
    char reply[BUFFER_SIZE + 1];
    ssize_t n = recvfrom(fd, reply, BUFFER_SIZE, 0, NULL, NULL);
    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) fprintf(stderr, "Timed out waiting for a reply.\n");
        else perror("recvfrom");
        close(fd); return EXIT_FAILURE;
    }
    reply[n] = '\0';
    printf("Echo: %s", reply);
    close(fd);
    return EXIT_SUCCESS;
}
