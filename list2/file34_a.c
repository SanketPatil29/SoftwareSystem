#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#define PORT 8080 
#define BUFFER_SIZE 1024

 // volatile sig_atomic_t serverRunning = 1;
int serverRunning = 1;

void signalHandler(int signo)
{
	if (signo == SIGINT || signo == SIGTERM)
	{
		serverRunning = 0;
	}
}
void handleClient(int clientSocket);

int main()
{
	int serverSocket, clientSocket;
	struct sockaddr_in serverAddress, clientAddress;
	socklen_t clientAddrLen = sizeof(clientAddress);

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
	{
		perror("Socket creation failed");
		exit(1);
	}

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
	{
		perror("Socket binding failed");
		exit(1);
	}

	if (listen(serverSocket, 5) == -1)
	{
		perror("Listening failed");
		exit(1);
	}

	printf("Server is listening on port %d...\n", PORT);
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);

	while (serverRunning)
	{
		int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddrLen);
		if (clientSocket == -1)
		{
			perror("Accepting connection failed");
			continue;
		}

		pid_t childPID = fork();
		if (childPID < 0)
		{
			perror("Fork failed");
		}
		else if (childPID == 0)
		{
			// Child process
			close(serverSocket); // Close the server socket in the child process
			handleClient(clientSocket);
			close(clientSocket);
			exit(0); // Terminate the child process
		}
		else
		{
			// Parent process
			close(clientSocket);		// Close the client socket in the parent process
			waitpid(-1, NULL, WNOHANG); // Cleanup zombie child processes
		}
	}

	// Close the server socket.
	close(serverSocket);
	return 0;
}

void handleClient(int clientSocket)
{
	char buffer[BUFFER_SIZE];
	int bytesRead;

	// Prompt the client to choose a role
	char rolePrompt[] = "\n Message from the server.";
	while (1)
	{
		memset(buffer,0,sizeof(buffer));
		send(clientSocket, rolePrompt, strlen(rolePrompt), 0);

		// Receive the client's role choice
		bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (bytesRead <= 0)
		{
			perror("Error receiving role choice");
			close(clientSocket);
			return;
		}
		buffer[bytesRead] = '\0';
		
        printf("client: %s", buffer);
        char response[] = "Communication terminated !!.\n";
        send(clientSocket, response, strlen(response), 0);
        close(clientSocket);
        return;
		
	}
	// Close the client socket
	close(clientSocket);
}