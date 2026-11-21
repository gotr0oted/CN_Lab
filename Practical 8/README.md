# Practical 8: Go-Back-N Sliding Window Simulation

## Aim
Demonstrate a sender window, cumulative acknowledgments, and retransmission after a frame loss.

## Build and run (Linux)
```sh
gcc -Wall -Wextra -pedantic go_back_n.c -o go_back_n
./go_back_n
```
Enter a frame count, window size, and one sequence number to drop once (`-1` for no loss). Run with and without loss. Explain how acknowledgment advances after retransmission and use your actual output.
