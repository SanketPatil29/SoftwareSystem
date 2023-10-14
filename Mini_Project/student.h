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


int authenticateStudent(int clientSocket)
{
    struct student student_info, temp_buffer;
    int fd = open("student_database.txt", O_RDONLY, 0644); // Open student database

    if (fd == -1)
    {
        perror("Error opening file");
        return 0;
    }

    bool found = false; // Initialize found to false
    char buffer[1024];  // Declare buffer for sending data

    // Prompt for Student ID
    send(clientSocket, "Enter Student ID: ", strlen("Enter Student ID: "), 0);

    // Read Student ID
    int readResult = read(clientSocket, student_info.student_id, sizeof(student_info.student_id) - 1);
    if (readResult <= 0)
    {
        send(clientSocket, "Error receiving student ID from server", strlen("Error receiving student ID from server"), 0);
        return 0;
    }
    student_info.student_id[readResult] = '\0';

    // Prompt for Student Password
    send(clientSocket, "Enter Student Password: ", strlen("Enter Student Password: "), 0);

    // Read Student Password
    readResult = read(clientSocket, student_info.password, sizeof(student_info.password) - 1);
    if (readResult <= 0)
    {
        send(clientSocket, "Error receiving student password from server", strlen("Error receiving student password from server"), 0);
        return 0;
    }
    student_info.password[readResult] = '\0';

    // Reset file pointer to the beginning
    lseek(fd, 0, SEEK_SET);

    // Loop to search for the student in the file
    while (read(fd, &temp_buffer, sizeof(temp_buffer)) > 0)
    {
        // Check if Student ID and Password match
        if ((strcmp(student_info.student_id, temp_buffer.student_id) == 0) && (strcmp(student_info.password, temp_buffer.password) == 0))
        {
            // Student found
            found = true;
            break;
        }
    }

    // Respond based on authentication result
    if (found)
    {
        send(clientSocket, "Authentication Success\n", strlen("Authentication Success\n"), 0);
        close(fd);
        return 1;
    }
    else
    {
        send(clientSocket, "Authentication Failed\n", strlen("Authentication Failed\n"), 0);
        close(fd);
        return 0;
    }
    return 0;
}


int student_functionality(int clientSocket) 
{
    if (authenticateStudent(clientSocket)) // Authenticated successfully.
    {
        char readbuff[1000], writebuff[1000]; // A buffer used for reading & writing to the client

        while (1)
        {
            char adminPrompt[] = "\nAdmin can Do:\n - 1. Add Student\n - 2. View Student Details\n - 3. Add Faculty\n - 4. View Faculty Details\n - 5. Activate Student\n - 6. Block Student\n - 7. Modify Student Details\n - 8. Modify Faculty Details\n - 9. Logout and Exit\n";
            send(clientSocket, adminPrompt, strlen(adminPrompt), 0);
            
            ssize_t readBytes = recv(clientSocket, readbuff, sizeof(readbuff), 0);
            if (readBytes == -1)
            {
                perror("Error in choice");
                return false;
            }
            int choice = atoi(readbuff);

            switch (choice)
            {
            case 1:
                    // addStudent(clientSocket);
                    break;
            case 2:
                    // viewStudent(clientSocket);
                    break;
            case 3:
                    // addFaculty(clientSocket);
                    break;
            case 4:
                    // viewFaculty(clientSocket);
                    break;
            // case 5: 
            //         activateStudent(clientSocket);
            //         break;
            // case 6:
            //         blockStudent(clientSocket);
            //         break;
            case 9:
                return 0; // Exit from admin menu.
            default:
                    break;
            }
        }
    }else{
        // Authentication Failed.
        return 0;
    }
}