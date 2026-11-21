# Practical 3: TCP Echo Client

## Aim
Connect to the TCP echo server from Practical 2 and exchange messages over a stream socket.

## Build and run (Linux)
```sh
gcc -Wall -Wextra -pedantic tcp_client.c -o tcp_client
./tcp_client 127.0.0.1
```
Start Practical 2 first. The optional argument is the server IPv4 address; the default is loopback. Enter `/quit` to disconnect.

## Procedure and result
The client connects to port 8080, sends each line, reads the echoed bytes, then closes. Test several messages and record output from your own run.
