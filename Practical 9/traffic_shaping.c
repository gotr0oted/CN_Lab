/* Practical 9: packet-level leaky and token bucket models. */
#include <stdio.h>
#include <stdlib.h>

#define MAX_SLOTS 100
static int min_int(int a, int b) { return a < b ? a : b; }

int main(void) {
    int capacity, token_capacity, refill, slots, arrivals[MAX_SLOTS];
    printf("Queue capacity (packets): ");
    if (scanf("%d", &capacity) != 1 || capacity < 1) { fprintf(stderr, "Invalid capacity.\n"); return EXIT_FAILURE; }
    printf("Token bucket capacity: ");
    if (scanf("%d", &token_capacity) != 1 || token_capacity < 1) { fprintf(stderr, "Invalid token capacity.\n"); return EXIT_FAILURE; }
    printf("Tokens added per time slot: ");
    if (scanf("%d", &refill) != 1 || refill < 1) { fprintf(stderr, "Invalid refill rate.\n"); return EXIT_FAILURE; }
    printf("Number of slots (1-%d): ", MAX_SLOTS);
    if (scanf("%d", &slots) != 1 || slots < 1 || slots > MAX_SLOTS) { fprintf(stderr, "Invalid slot count.\n"); return EXIT_FAILURE; }
    for (int i = 0; i < slots; ++i) {
        printf("Packets arriving at slot %d: ", i + 1);
        if (scanf("%d", &arrivals[i]) != 1 || arrivals[i] < 0) { fprintf(stderr, "Invalid arrival count.\n"); return EXIT_FAILURE; }
    }
    int leak_queue = 0, token_queue = 0, tokens = token_capacity;
    puts("\nSlot | Arrivals | Leaky sent | Leaky dropped | Token sent | Token dropped | Tokens left");
    for (int i = 0; i < slots; ++i) {
        int leak_drop = arrivals[i] > capacity - leak_queue ? arrivals[i] - (capacity - leak_queue) : 0;
        leak_queue += arrivals[i] - leak_drop;
        int leak_sent = min_int(leak_queue, refill);
        leak_queue -= leak_sent;
        tokens = min_int(token_capacity, tokens + refill);
        int token_drop = arrivals[i] > capacity - token_queue ? arrivals[i] - (capacity - token_queue) : 0;
        token_queue += arrivals[i] - token_drop;
        int token_sent = min_int(token_queue, tokens);
        token_queue -= token_sent;
        tokens -= token_sent;
        printf("%4d | %8d | %10d | %13d | %10d | %13d | %11d\n",
               i + 1, arrivals[i], leak_sent, leak_drop, token_sent, token_drop, tokens);
    }
    printf("\nLeaky queue remaining: %d; token-bucket queue remaining: %d.\n", leak_queue, token_queue);
    return EXIT_SUCCESS;
}
