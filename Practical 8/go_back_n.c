/* Practical 8: deterministic Go-Back-N ARQ demonstration. */
#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 100

int main(void) {
    int count, window, drop_once;
    printf("Number of frames (1-%d): ", MAX_FRAMES);
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_FRAMES) {
        fprintf(stderr, "Invalid frame count.\n"); return EXIT_FAILURE;
    }
    printf("Window size (1-%d): ", count);
    if (scanf("%d", &window) != 1 || window < 1 || window > count) {
        fprintf(stderr, "Invalid window size.\n"); return EXIT_FAILURE;
    }
    printf("Sequence number to drop once (-1 for no loss): ");
    if (scanf("%d", &drop_once) != 1 || drop_once < -1 || drop_once >= count) {
        fprintf(stderr, "Invalid drop sequence.\n"); return EXIT_FAILURE;
    }
    int base = 0, loss_pending = drop_once >= 0;
    while (base < count) {
        int end = base + window < count ? base + window : count;
        printf("\nSender transmits window [%d..%d]\n", base, end - 1);
        int gap = -1;
        for (int seq = base; seq < end; ++seq) {
            printf("Send frame %d: ", seq);
            if (loss_pending && seq == drop_once) {
                puts("simulated loss"); loss_pending = 0; gap = seq; break;
            }
            if (gap >= 0) { puts("receiver discards out-of-order frame"); continue; }
            printf("receiver accepts; ACK %d\n", seq + 1);
        }
        if (gap >= 0) {
            printf("Timeout at base %d; retransmit from frame %d.\n", base, base);
            continue;
        }
        base = end;
    }
    puts("\nAll frames acknowledged.");
    return EXIT_SUCCESS;
}
