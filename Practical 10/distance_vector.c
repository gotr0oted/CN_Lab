/* Practical 10: distance-vector routing for up to 10 routers. */
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROUTERS 10
#define INF 9999

int main(void) {
    int n, link[MAX_ROUTERS][MAX_ROUTERS];
    int distance[MAX_ROUTERS][MAX_ROUTERS], next_hop[MAX_ROUTERS][MAX_ROUTERS];
    printf("Number of routers (1-%d): ", MAX_ROUTERS);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_ROUTERS) {
        fprintf(stderr, "Invalid router count.\n"); return EXIT_FAILURE;
    }
    printf("Enter the %d x %d link-cost matrix (use %d for no link):\n", n, n, INF);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        if (scanf("%d", &link[i][j]) != 1 || link[i][j] < 0) {
            fprintf(stderr, "Costs must be nonnegative integers.\n"); return EXIT_FAILURE;
        }
        if (i == j) link[i][j] = 0;
        distance[i][j] = link[i][j];
        next_hop[i][j] = i == j ? i : (link[i][j] < INF ? j : -1);
    }
    for (int round = 0; round < n - 1; ++round) {
        int changed = 0;
        for (int router = 0; router < n; ++router)
            for (int neighbor = 0; neighbor < n; ++neighbor) {
                if (router == neighbor || link[router][neighbor] >= INF) continue;
                for (int dest = 0; dest < n; ++dest) {
                    if (distance[neighbor][dest] >= INF) continue;
                    int candidate = link[router][neighbor] + distance[neighbor][dest];
                    if (candidate < distance[router][dest]) {
                        distance[router][dest] = candidate;
                        next_hop[router][dest] = neighbor;
                        changed = 1;
                    }
                }
            }
        if (!changed) break;
    }
    for (int router = 0; router < n; ++router) {
        printf("\nRouter %d routing table\nDestination\tCost\tNext hop\n", router + 1);
        for (int dest = 0; dest < n; ++dest) {
            printf("%d\t\t", dest + 1);
            if (distance[router][dest] >= INF) printf("INF\t");
            else printf("%d\t", distance[router][dest]);
            if (next_hop[router][dest] < 0) puts("-");
            else printf("%d\n", next_hop[router][dest] + 1);
        }
    }
    return EXIT_SUCCESS;
}
