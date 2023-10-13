#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/socket.h>
#include "structure.h"

int authenticateFaculty(int clientSocket)
{
    char username[100];
    char pass[100];

    // Send a prompt for the username
    const char *userPrompt = "\nEnter login id of faculty: ";
    send(clientSocket, userPrompt, strlen(userPrompt), 0);

    // Receive the username from the client
    ssize_t bytesRead = recv(clientSocket, username, sizeof(username), 0);
    if (bytesRead <= 0)
    {
        close(clientSocket);
        return false;
    }
    if (username[bytesRead - 1] == '\n')
    {
        username[bytesRead - 1] = '\0';
    }
    else
    {
        username[bytesRead] = '\0';
    }

    // Send a prompt for the password
    const char *passPrompt = "\nEnter password of the Admin: ";
    send(clientSocket, passPrompt, strlen(passPrompt), 0);

    // Receive the password from the client
    bytesRead = recv(clientSocket, pass, sizeof(pass), 0);
    if (bytesRead <= 0)
    {
        close(clientSocket);
        return false;
    }
    if (pass[bytesRead - 1] == '\n')
    {
        pass[bytesRead - 1] = '\0';
    }
    else
    {
        pass[bytesRead] = '\0';
    }

    int fd = open("faculty_database.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening the file\n");
        close(fd);
        send(clientSocket, "Error reading faculty details\n", strlen("Error reading faculty details\n"), 0);
        return 1;
    }
    // Use flock to apply mandatory lock
    if (flock(fd, LOCK_SH) == -1) {
        perror("Error applying lock");
        close(fd);
        send(clientSocket, "Error reading faculty details\n", strlen("Error reading faculty details\n"), 0);
        return 1;
    }

    // Read faculty details from the file and send the details of the specified faculty ID to the client
    struct faculty faculty_info;
    ssize_t facultyFound = 0;
    while (read(fd, &faculty_info, sizeof(struct faculty)) > 0) {
        if (strcmp(faculty_info.faculty_id, username) == 0) {
            // Found the faculty with the specified ID, send details to the client
            if (strcmp(faculty_info.password, pass) == 0){
                facultyFound = 1;
            }
            break;
        }
    }

    if (facultyFound) 
    {  // Authentication successful
        char * success_msg = "Authentication successful\n"; ///
        send(clientSocket, success_msg, strlen(success_msg), 0);
        return true;
    }
    else{
    // Authentication failed
    char * failure_msg = "Authentication failed\n"; ///
    send(clientSocket, failure_msg, strlen(failure_msg), 0);
    close(clientSocket);
    return false;
    }
}


//Returns 1 if login successfully
int faculty_functionality(int clientSocket) 
{
    if (authenticateFaculty(clientSocket))
    {
        char readbuff[1000], writebuff[1000]; // A buffer used for reading & writing to the client
        while (1)
        {
            char * login_msg = "\nLogin Successfully\n";
            send(clientSocket, login_msg, strlen(login_msg), 0);///
            char adminPrompt[] = "\nAdmin can Do:\n - 1. Add Student\n - 2. View Student Details\n - 3. Add Faculty\n - 4. View Faculty Details\n - 5. Activate Student\n - 6. Block Student\n - 7. Modify Student Details\n - 8. Modify Faculty Details\n - 8. Logout and Exit\n";

            send(clientSocket, adminPrompt, strlen(adminPrompt), 0);
            //readBytes store no of bytes read from the client by the server
            ssize_t readBytes = recv(clientSocket, readbuff, sizeof(readbuff), 0);
            if (readBytes == -1)
            {
                perror("Error in the choice you provided");
                return false;
            }
            int choice = atoi(readbuff);
            //send(clientSocket,readbuff,sizeof(readbuff),0);

            // switch (choice)
            // {
            // case 1:
            //         addStudent(clientSocket);
            //         break;
            // case 2:
            //         viewStudent(clientSocket);
            //         break;
            // case 3:
            //         addFaculty(clientSocket);
            //         break;
            // case 4:
            //         viewFaculty(clientSocket);
            //         break;
            // case 5: 
            //         activateStudent(clientSocket);
            //         break;
            // case 6:
            //         blockStudent(clientSocket);
            //         break;
            // case 8:
            //     return 0;
            // default:
            //         break;
            // }
        }
    }
    else{
        return 0;
    }
}