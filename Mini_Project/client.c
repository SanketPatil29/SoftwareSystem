/*
Name: Sanket S. Patil (MT2023051).

	Client program for connecting with server
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

int main(int argc,char* argv[]) {
    if(argc!=2){
        perror("Mention port no as well");
        return 0;
    }
    int clientSocket;
    struct sockaddr_in serverAddress;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(atoi(argv[1]));
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connecting with the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Connection failed");
        close(clientSocket);
        exit(1);
    }
    printf("You are now connected to the server\n");

    while (1) {
        // Receive data from the server
        char buffer[1024];
        memset(buffer, '\0', sizeof(buffer));
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            perror("Error receiving data");
            break;
        }

        // Display received data
        printf("%s\n", buffer);

        // Send a response (optional)
        char message[1024];
      
        memset(message, 0, sizeof(message));
        fgets(message, sizeof(message), stdin);
        send(clientSocket, message, strlen(message), 0);
    }
    close(clientSocket);

    return 0;
}