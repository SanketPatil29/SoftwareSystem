#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "faculty.h"
#include "admin.h"
#include "student.h"
#define BUFFER_SIZE 1024
int serverRunning = 1;

void signalHandler(int signo)
{
	if (signo == SIGINT || signo == SIGTERM)
	{
		serverRunning = 0;
	}
}

void handleClient(int clientSocket)
{
	char buffer[BUFFER_SIZE];
	int bytesRead;
	
	char rolePrompt[] = "\nEnter login type:\n1. Admin\n2. Professor\n3. Student\n";
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
		
		// Admin
		if (buffer[0] == '1')
		{
			char response[] = "----------Admin----------\n";
			send(clientSocket, response, strlen(response), 0);
			if(!admin_functionality(clientSocket))continue;
		}
		// Faculty
		else if (buffer[0] == '2')
		{
			char response[] = "----------Faculty----------\n";
			send(clientSocket, response, strlen(response), 0);
			if(!faculty_functionality(clientSocket))continue;
		}
		// Student
		else if (buffer[0] == '3')
		{
			char response[] = "----------Student----------\n";
			send(clientSocket, response, strlen(response), 0);
			if(!student_functionality(clientSocket))continue;
		}
		// Invalid response
		else
		{
			char response[] = "Invalid login type input!\n";
			send(clientSocket, response, strlen(response), 0);
		}
	}
	// Close the client socket
	close(clientSocket);
}


int main(int argc,char *argv[])
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
	serverAddress.sin_port = htons(atoi(argv[1]));
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

	printf("Server is Listening on Port %s...\n", argv[1]);
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);

	while (serverRunning)
	{
		// Connecting with the client.
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
			exit(0); // Terminates the child process
		}
		else
		{
			// Parent process
			close(clientSocket);		// Close the client socket in the parent process
			waitpid(-1, NULL, WNOHANG); // Cleanup zombie child processes
		}
	}
	close(serverSocket);
	return 0;
}