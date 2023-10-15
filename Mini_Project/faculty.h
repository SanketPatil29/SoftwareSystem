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

void updateDetails(int clientSocket){
    char course_id[10];
    char update_field[10];
    char update_value[10];

    // Ask the client for the course ID to be updated
    send(clientSocket, "Enter Course ID to update: ", strlen("Enter Course ID to update: "), 0);
    int r = recv(clientSocket, course_id, sizeof(course_id), 0);
    if (r <= 0)
    {
        close(clientSocket);
        return;
    }
    if (course_id[r - 1] == '\n')
    {
        course_id[r - 1] = '\0';
    }
    else{
    course_id[r] = '\0';
    }
    // Open the course database file for reading and writing
    int fd = open("course_database.txt", O_RDWR, 0666);
    if (fd == -1) {
        perror("Error opening file");
        send(clientSocket, "Error updating course details\n", strlen("Error updating course details\n"), 0);
        return;
    }

    struct course temp_course;
    int courseFound = 0;

    // Loop through the file and find the course by course_id
    while (read(fd, &temp_course, sizeof(temp_course)) > 0) {
        printf("%s %s\n", course_id, temp_course.course_id);
        if (strcmp(course_id, temp_course.course_id) == 0) {
            courseFound = 1;

            // Ask the client for the field to update
            send(clientSocket, "Choose field to update: ", strlen("Choose field to update: "), 0);
            r =  recv(clientSocket, update_field, sizeof(update_field), 0);
            update_field[r] = '\0';

            // Ask the client for the new value
            send(clientSocket, "Enter new value: ", strlen("Enter new value: "), 0);
            r = recv(clientSocket, update_value, sizeof(update_value), 0);
            update_value[r] = '\0';

            // Update the chosen field
            if (strcmp(update_field, "name") == 0) {
                strncpy(temp_course.course_name, update_value, sizeof(temp_course.course_name) - 1);
            } else if (strcmp(update_field, "seats") == 0) {
                strncpy(temp_course.seats, update_value, sizeof(temp_course.seats) - 1);
            } else if (strcmp(update_field, "credits") == 0) {
                strncpy(temp_course.credits, update_value, sizeof(temp_course.credits) - 1);
            }else if (strcmp(update_field, "department") == 0) {
                strncpy(temp_course.credits, update_value, sizeof(temp_course.department) - 1);
            } else {
                send(clientSocket, "Invalid field specified\n", strlen("Invalid field specified\n"), 0);
                close(fd);
                return;
            }

            // Move the file pointer back by the size of the course structure
            lseek(fd, -sizeof(struct course), SEEK_CUR);
            // Write the updated course information back to the file
            write(fd, &temp_course, sizeof(temp_course));

            send(clientSocket, "Course details updated successfully\n", strlen("Course details updated successfully\n"), 0);
            break;
        }
    }

    if (!courseFound) {
        send(clientSocket, "Course not found\n", strlen("Course not found\n"), 0);
    }

    close(fd);
}

void removeCourseFromCatalog(int clientSocket) {
    char course_id[50];

    // Ask the client for the course ID to be removed
    send(clientSocket, "Enter Course ID to remove from catalog: ", strlen("Enter Course ID to remove from catalog: "), 0);
    int r = recv(clientSocket, course_id, sizeof(course_id), 0);
    if (r <= 0)
    {
        close(clientSocket);
        return;
    }
    if (course_id[r - 1] == '\n')
    {
        course_id[r - 1] = '\0';
    }
    else{
        course_id[r] = '\0';
    }
    // Remove the course from the catalog
    struct course temp_course;

    int fd = open("course_database.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        send(clientSocket, "Error removing course from catalog\n", strlen("Error removing course from catalog\n"), 0);
        return;
    }

    int courseFound = 0;

    // Loop through the file and find the course by course_id
    while (read(fd, &temp_course, sizeof(temp_course)) > 0) {
        if (strcmp(course_id, temp_course.course_id) == 0) {
            // Found the course, write a null string to course_id field
            lseek(fd, -sizeof(struct course), SEEK_CUR);
            memset(&temp_course, '\0', sizeof(temp_course));
            write(fd, &temp_course, sizeof(temp_course));
            courseFound = 1;
            break;
        }
    }


    struct student_course s_c;
    // Open the course database file for reading and writing
    int fd2 = open("student_course.txt", O_RDWR);
    if (fd2 == -1) {
        perror("Error opening file");
        send(clientSocket, "Error enrolling in course\n", strlen("Error enrolling in course\n"), 0);
        return;
    }
    while (read(fd2, &s_c, sizeof(s_c)) > 0) {
        if(strcmp(course_id, s_c.course_id) == 0) {
            // Found the course, write a null string to course_id field
            lseek(fd2, -sizeof(struct student_course), SEEK_CUR);
            memset(&s_c.course_id, '\0', sizeof(s_c.course_id));
            write(fd2, &s_c, sizeof(s_c));
        }
    }
    close(fd2);
    close(fd);
}


void viewCourse(int clientSocket) {
    struct course temp_course,t;

    // Receive course ID from the client
    send(clientSocket, "Enter Course ID to View Details: ", strlen("Enter Course ID to View Details: "), 0);
    int bytesRead = recv(clientSocket, t.course_id, sizeof(t.course_id), 0);
     if(bytesRead <= 0)
    {
        close(clientSocket);
        return;
    }
    if(t.course_id[bytesRead - 1] == '\n')
    {
        t.course_id[bytesRead - 1] = '\0';
    }
    else
    {
        t.course_id[bytesRead] = '\0';
    }

    // Open the course database file for reading
    int fd = open("course_database.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        send(clientSocket, "Error viewing course details\n", strlen("Error viewing course details\n"), 0);
        return;
    }

    bool found = false;

    //Loop to search for the course in the file
    //memset(temp_course.course_id, '\0', sizeof(temp_course));
    while(read(fd, &temp_course, sizeof(temp_course)) > 0) {
        // Check if the course ID matches
        int res = strcmp(t.course_id, temp_course.course_id);
    
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

    send(clientSocket, "Enter the Course_id ", strlen("Enter the Course_id "), 0);
    int bytesRead = recv(clientSocket, new_course.course_id, sizeof(new_course.course_id), 0);
    if (bytesRead <= 0) {
        perror("Error while receiving  ID");
        return;
    }
    if(bytesRead <= 0)
    {
        close(clientSocket);
        return;
    }
    if(new_course.course_id[bytesRead - 1] == '\n')
    {
        new_course.course_id[bytesRead - 1] = '\0';
    }
    else
    {
        new_course.course_id[bytesRead] = '\0';
    }

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
                    removeCourseFromCatalog(clientSocket);
                    break;
            case 4:
                    updateDetails(clientSocket);
                    break;
            // case 5: 
                    // activateStudent(clientSocket);
                    // break;
            case 6:
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