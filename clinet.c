#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket");
    }

    // Set up server connection
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with server IP address
    server.sin_family = AF_INET;
    server.sin_port = htons(8888); // Replace with server port number

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connect failed. Error");
        return 1;
    }

    printf("Connected to server\n");

    // Communicate with server
    while (1) {
        printf("Enter message: ");
        fgets(message, sizeof(message), stdin);

        // Send message to server
        if (send(sock, message, strlen(message), 0) < 0) {
            puts("Send failed");
            return 1;
        }

        // Receive reply from server
        if (recv(sock, server_reply, 2000, 0) < 0) {
            puts("recv failed");
            break;
        }

        printf("Server reply: %s\n", server_reply);
    }

    close(sock);
    return 0;
}
