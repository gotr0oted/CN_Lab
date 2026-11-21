# Practical 10: Distance-Vector Routing

## Aim
Compute routing tables by iteratively exchanging neighbors' distance vectors until no route improves.

## Build and run (Linux)
```sh
gcc -Wall -Wextra -pedantic distance_vector.c -o distance_vector
./distance_vector
```
Enter up to 10 routers and a square link-cost matrix. Use 0 on the diagonal and 9999 for no direct link; link costs must be nonnegative.

## Procedure and result
The program applies Bellman-Ford distance-vector updates and prints each destination cost and next hop. Try a small topology, then remove a link and compare routes using your own output.
