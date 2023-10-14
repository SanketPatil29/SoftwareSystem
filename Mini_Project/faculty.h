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

void viewCourse(int clientSocket) {
    char search_course_id[50];
    struct course temp_course,t;

    // Receive course ID from the client
    send(clientSocket, "Enter Course ID to View Details: ", strlen("Enter Course ID to View Details: "), 0);
    int bytesRead = recv(clientSocket, t.course_id, sizeof(t.course_id), 0);
     if(bytesRead <= 0)
    {
        close(clientSocket);
        return;
    }
    if(search_course_id[bytesRead - 1] == '\n')
    {
        search_course_id[bytesRead - 1] = '\0';
    }
    else
    {
        search_course_id[bytesRead] = '\0';
    }

    // Open the course database file for reading
    int fd = open("course_database.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        send(clientSocket, "Error viewing course details\n", strlen("Error viewing course details\n"), 0);
        return;
    }

    bool found = false;

    // Loop to search for the course in the file
    //memset(temp_course.course_id, '\0', sizeof(temp_course));
    while (read(fd, &temp_course, sizeof(temp_course)) > 0) {
        // Check if the course ID matches
        printf("%s %s\n", search_course_id, temp_course.course_id);
        int res = strcmp(t.course_id, temp_course.course_id);
        printf("%d\n", res);
        if (res == 0) {
            // Send course details to the client
            char facultyDetailsBuffer[1024];
            snprintf(facultyDetailsBuffer, sizeof(facultyDetailsBuffer), "Name: %s\nDepartment: %s\nSeats: %s\nCredits: %s\n",
                    temp_course.course_name, temp_course.department, temp_course.seats, temp_course.credits);
            send(clientSocket, facultyDetailsBuffer, strlen(facultyDetailsBuffer), 0);
            found = true;
            break;
        }
        memset(temp_course.course_id, '\0', sizeof(temp_course));
    }

    // If the course is not found, send a message to the client
    if (!found) {
        send(clientSocket, "Course not found\n", strlen("Course not found\n"), 0);
    }

    close(fd);
}
void addCourse(int clientSocket) {
    struct course new_course;

    // Receive course details from the client
    // send(clientSocket, "Enter Course ID: ", strlen("Enter Course ID: "), 0);
    // memset(new_course.course_id, '\0', sizeof(new_course.course_id));
    // int bytesRead = recv(clientSocket, new_course.course_id, sizeof(new_course.course_id) - 1, 0);
    // new_course.course_id[bytesRead] = '\0';

    send(clientSocket, "Enter the Course_id ", strlen("Enter the Couuse-ID: "), 0);
    int bytesRead = recv(clientSocket, new_course.course_id, sizeof(new_course.course_id), 0);
    if (bytesRead <= 0) {
        perror("Error while receiving  ID");
        return;
    }
    new_course.course_id[bytesRead] = '\0';

    send(clientSocket, "Enter Course Name: ", strlen("Enter Course Name: "), 0);
    bytesRead = recv(clientSocket, new_course.course_name, sizeof(new_course.course_name) - 1, 0);
    new_course.course_name[bytesRead] = '\0';

    send(clientSocket, "Enter Department: ", strlen("Enter Department: "), 0);
    bytesRead = recv(clientSocket, new_course.department, sizeof(new_course.department) - 1, 0);
    new_course.department[bytesRead] = '\0';

    send(clientSocket, "Enter Number of Seats: ", strlen("Enter Number of Seats: "), 0);
    bytesRead = recv(clientSocket, new_course.seats, sizeof(new_course.seats)-1, 0);
    new_course.seats[bytesRead] = '\0';

    send(clientSocket, "Enter Credits: ", strlen("Enter Credits: "), 0);
    bytesRead = recv(clientSocket, new_course.credits, sizeof(new_course.credits)-1, 0);
    new_course.credits[bytesRead] = '\0';

    // Additional checks to ensure proper string termination
    new_course.course_id[sizeof(new_course.course_id) - 1] = '\0';
    new_course.course_name[sizeof(new_course.course_name) - 1] = '\0';
    new_course.department[sizeof(new_course.department) - 1] = '\0';

    // Open the course database file for appending
    // Open the file to enter this data in the database
    int fd = open("course_database.txt", O_WRONLY | O_APPEND | O_CREAT, 0666); // Open the file in append mode

    if (fd == -1) {
        perror("Error opening the file\n");
        close(fd);
        return;
    }

    // Use flock to apply mandatory lock
    if (flock(fd, LOCK_EX) == -1) {
        perror("Error applying lock");
        close(fd);
        return;
    }

    // Use lseek to move the file pointer to the end of the file
    if (lseek(fd, 0, SEEK_END) == -1) {
        perror("Error using lseek");
        flock(fd, LOCK_UN); // Release the lock before closing the file
        close(fd);
        return;
    }

    // Write the structure data to the file
    if (write(fd, &new_course, sizeof(struct course)) == -1) {
        perror("Error writing to the file");
        flock(fd, LOCK_UN); // Release the lock before closing the file
        close(fd);
        return;
    }

    flock(fd, LOCK_UN); // Release the lock
    close(fd);          // Close the file
}

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
            char adminPrompt[] = "\n----------Faculty Menu----------\n - 1. View offering courses\n - 2. Add new course\n - 3. Remove course from catalog\n - 4. Update course details\n - 5. Change password\n - 6. Logout and exit\n Enter your choice: ";

            send(clientSocket, adminPrompt, strlen(adminPrompt), 0);
            //readBytes store no of bytes read from the client by the server
    
            int readBytes = recv(clientSocket, readbuff, sizeof(readbuff), 0);
        
            if (readBytes == -1)
            {
                perror("Error in the choice you provided");
                return false;
            }
            int choice = atoi(readbuff);
            switch (choice)
            {
            case 1:
                    viewCourse(clientSocket);
                    break;
            case 2:
                    addCourse(clientSocket);
                    break;
            case 3:
                    // addFaculty(clientSocket);
                    break;
            case 4:
                    // viewFaculty(clientSocket);
                    break;
            case 5: 
                    // activateStudent(clientSocket);
                    break;
            case 8:
                return 0;
            default:
                    break;
            }
        }
    }
    else{
        return 0;
    }
}