#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void *handle_client(void *arg) {
    int client_sock = *(int *)arg;
    char buffer[1024];
    int n;

    while ((n = recv(client_sock, buffer, sizeof(buffer), 0)) > 0) {
        printf("Received message: %s", buffer);
        send(client_sock, "Server received your message.\n", strlen("Server received your message.\n"), 0);
    }

    close(client_sock);
    return NULL;
}
