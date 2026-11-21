/* Practical 5: UDP echo server (IPv4, port 9090). */
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 9090
#define BUFFER_SIZE 1024

int main(void) {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) { perror("socket"); return EXIT_FAILURE; }
    struct sockaddr_in local;
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(PORT);
    if (bind(fd, (struct sockaddr *)&local, sizeof(local)) < 0) {
        perror("bind"); close(fd); return EXIT_FAILURE;
    }
    printf("UDP echo server listening on port %d\n", PORT);
    for (;;) {
        char buffer[BUFFER_SIZE];
        struct sockaddr_in peer;
        socklen_t peer_length = sizeof(peer);
        ssize_t n = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&peer, &peer_length);
        if (n < 0) {
            if (errno == EINTR) continue;
            perror("recvfrom"); break;
        }
        char address[INET_ADDRSTRLEN] = "?";
        (void)inet_ntop(AF_INET, &peer.sin_addr, address, sizeof(address));
        printf("Received %zd bytes from %s:%u\n", n, address, ntohs(peer.sin_port));
        if (sendto(fd, buffer, (size_t)n, 0, (struct sockaddr *)&peer, peer_length) < 0) perror("sendto");
    }
    close(fd);
    return EXIT_SUCCESS;
}
