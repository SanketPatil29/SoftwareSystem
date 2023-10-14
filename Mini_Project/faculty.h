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
    struct faculty faculty_info, temp_buffer;
    int fd = open("faculty_database.txt", O_RDONLY, 0644);

    if ( fd == -1)
    {
        perror("Error opening file");
        return 0;
    }

    bool found = false;
    char buffer[1024];
    send(clientSocket, "Enter FacultyID: ", strlen("Enter FacultyID: "), 0);

    // Faculty ID
    int readResult = read(clientSocket, faculty_info.faculty_id, sizeof(faculty_info.faculty_id) - 1);
    if (readResult <= 0)
    {
        send(clientSocket, "Error receiving faculty username from server", strlen("Error receiving faculty username from server"), 0);
        return 0;
    }
    faculty_info.faculty_id[readResult] = '\0';

    send(clientSocket, "Enter Faculty Password: ", strlen("Enter Faculty Password: "), 0);

    // Faculty Password
    readResult = read(clientSocket, faculty_info.password, sizeof(faculty_info.password) - 1);
    if (readResult <= 0)
    {
        send(clientSocket, "Error receiving faculty password from server", strlen("Error receiving faculty password from server"), 0);
        return 0;
    }
    faculty_info.password[readResult] = '\0';

    lseek(fd, 0, SEEK_SET);
    while (read(fd, &temp_buffer, sizeof(temp_buffer)) > 0)
    {
        if ((strcmp(faculty_info.faculty_id, temp_buffer.faculty_id) == 0) && (strcmp(faculty_info.password, temp_buffer.password) == 0))
        {
            // Faculty found
            found = true;
            break;
        }
    }

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


int faculty_functionality(int clientSocket) 
{
    if (authenticateFaculty(clientSocket))
    {
        char readbuff[1000], writebuff[1000]; // A buffer used for reading & writing to the client
        while (1)
        {
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