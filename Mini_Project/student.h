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

char* intToString(int num) {
    // Determine the number of digits in the integer
    int digits = snprintf(NULL, 0, "%d", num);
    
    // Allocate memory for the string representation (including the null terminator)
    char *str = (char *)malloc(digits + 1);
    
    if (str == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Convert integer to string
    snprintf(str, digits + 1, "%d", num);

    return str;
}

// Function to view all course names
void viewAllCourses(int clientSocket) {
    struct course temp_course;

    int fd = open("course_database.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        send(clientSocket, "Error viewing course details\n", strlen("Error viewing course details\n"), 0);
        return;
    }

    int courseNumber = 1;

    // Loop to read and send all course names
    while (read(fd, &temp_course, sizeof(temp_course)) > 0) {
        // Send course name in the specified format to the client
        if (!strlen(temp_course.course_name))continue;
        char courseInfo[150];
        // snprintf(courseInfo, sizeof(courseInfo), "%d - %s\n", courseNumber, temp_course.course_name);
        snprintf(courseInfo, sizeof(courseInfo), "%d - Course ID: %s - Name: %s\n", courseNumber, temp_course.course_id, temp_course.course_name);
        send(clientSocket, courseInfo, strlen(courseInfo), 0);
        courseNumber++;
    }

    // Signal the end of course names
    send(clientSocket, "End of Course Names\n", strlen("End of Course Names\n"), 0);

    close(fd);
}

void enrollNewCourse(int clientSocket) {
    char student_id[50];
    char course_id[50];

    // Ask the client for student ID
    send(clientSocket, "Enter Student ID: ", strlen("Enter Student ID: "), 0);
    recv(clientSocket, student_id, sizeof(student_id), 0);
    

    // Ask the client for course ID to enroll
    send(clientSocket, "Enter Course ID to enroll: ", strlen("Enter Course ID to enroll: "), 0);
    int bytesRead = recv(clientSocket, course_id, sizeof(course_id), 0);
     if(bytesRead <= 0)
    {
        close(clientSocket);
        return ;
    }
    if(course_id[bytesRead - 1] == '\n')
    {
        course_id[bytesRead - 1] = '\0';
    }
    else
    {
        course_id[bytesRead] = '\0';
    }

    // Check if the student is already enrolled in the course
    int isEnrolled = 0;

    // Open the student_course.txt file for reading
    int studentCourseFile = open("student_course.txt", O_RDWR | O_APPEND | O_CREAT, 0666);
    if (studentCourseFile != -1) {
        struct student_course temp_entry;

        // Loop through the file to check if the student is already enrolled
        while (read(studentCourseFile, &temp_entry, sizeof(struct student_course)) > 0) {
            // Check if the student is already enrolled in the course
            if (strcmp(student_id, temp_entry.student_id) == 0 && strcmp(course_id, temp_entry.course_id) == 0) {
                isEnrolled = 1;
                break;
            }
        }
    }

    if (isEnrolled) {
        send(clientSocket, "Student is already enrolled in the course\n", strlen("Student is already enrolled in the course\n"), 0);
        return;
    } else {

        struct course temp_course;
        // Open the course database file for reading and writing
        int fd = open("course_database.txt", O_RDWR);
        if (fd == -1) {
            perror("Error opening file");
            send(clientSocket, "Error enrolling in course\n", strlen("Error enrolling in course\n"), 0);
            return;
        }

        // Loop to search for the course in the file
        int seat = 0;
        int found_c = 0;
        while (read(fd, &temp_course, sizeof(struct course)) > 0) {
            // Check if the course ID matches
            seat = atoi(temp_course.seats);
            if (strcmp(course_id, temp_course.course_id) == 0) {
                // Check if there are available seats
                found_c = 1;
                if (seat > 0) {
                    struct student_course new_entry;

                    // Decrement the number of available seats by 1
                    seat--;

                    // Move the file pointer back by the size of the course structure
                    lseek(fd, -sizeof(struct course), SEEK_CUR);
                    strncpy(temp_course.seats, intToString(seat), sizeof(temp_course.seats) - 1); 
                    // Write the updated course information back to the file
                    write(fd, &temp_course, sizeof(struct course));

                    // Create an instance of struct student_course and write it to the file
                    strcpy(new_entry.student_id, student_id);
                    strcpy(new_entry.course_id, course_id);

                    // Write the student_course struct to the file
                    write(studentCourseFile, &new_entry, sizeof(struct student_course));

                    send(clientSocket, "Enrollment Success\n", strlen("Enrollment Success\n"), 0);
                } else {
                    send(clientSocket, "No available seats\n", strlen("No available seats\n"), 0);
                }

                break;
            }
        }

        // If the course is not found, send a message to the client
        if (found_c == 0) {
            send(clientSocket, "Course not found\n", strlen("Course not found\n"), 0);
        }

        close(fd);
    }
}



// void enrollNewCourse(int clientSocket) {
//     char student_id[50];
//     char course_id[50];

//     // Ask the client for student ID
//     send(clientSocket, "Enter Student ID: ", strlen("Enter Student ID: "), 0);
//     recv(clientSocket, student_id, sizeof(student_id), 0);

//     // Ask the client for course ID to enroll
//     send(clientSocket, "Enter Course ID to enroll: ", strlen("Enter Course ID to enroll: "), 0);
//     recv(clientSocket, course_id, sizeof(course_id), 0);

//     // Check if the student is already enrolled in the course
//     int isEnrolled = 0;

//     // Open the student_course.txt file for reading
//     int studentCourseFile = open("student_course.txt",O_CREAT | O_RDWR);
//     if (studentCourseFile != -1) {
//         struct student_course temp_entry;

//         // Loop through the file to check if the student is already enrolled
//         while (read(studentCourseFile, &temp_entry, sizeof(struct student_course)) > 0) {
//             // Check if the student is already enrolled in the course
//             if (strcmp(student_id, temp_entry.student_id) == 0 && strcmp(course_id, temp_entry.course_id) == 0) {
//                 isEnrolled = 1;
//                 break;
//             }
//         }

//         close(studentCourseFile);
//     }

//     if (isEnrolled) {
//         send(clientSocket, "Student is already enrolled in the course\n", strlen("Student is already enrolled in the course\n"), 0);
//         return;
//     } 
//     else {

//         struct course temp_course;
//         // // Receive course ID from the client
//         // send(clientSocket, "Enter Course ID to Enroll: ", strlen("Enter Course ID to Enroll: "), 0);
//         // recv(clientSocket, enroll_course_id, sizeof(enroll_course_id), 0);

//         // Open the course database file for reading and writing
//         int fd = open("course_database.txt", O_RDWR);
//         if (fd == -1) {
//             perror("Error opening file");
//             send(clientSocket, "Error enrolling in course\n", strlen("Error enrolling in course\n"), 0);
//             return;
//         }

//         // Loop to search for the course in the file
//         int seat = 0;
//         int found_c = 0;
//         while (read(fd, &temp_course, sizeof(temp_course)) > 0) {
//             // Check if the course ID matches
//             seat = atoi(temp_course.seats);
//             if (strcmp(course_id, temp_course.course_id) == 0) {
//                 // Check if there are available seats
//                 found_c = 1;
//                 if (seat > 0) {
//                     struct student_course new_entry;

//                     // Decrement the number of available seats by 1
//                     seat--;

//                     // Move the file pointer back by the size of the course structure
//                     lseek(fd, -sizeof(struct course), SEEK_CUR);
//                     strncpy(temp_course.seats, intToString(seat), sizeof(temp_course.seats) - 1); 
//                     // Write the updated course information back to the file
//                     write(fd, &temp_course, sizeof(struct course));

//                     // Create an instance of struct student_course and write it to the file
//                     strcpy(new_entry.student_id, student_id);
//                     strcpy(new_entry.course_id, course_id);

//                     // Write the student_course struct to the file
//                     write(studentCourseFile, &new_entry, sizeof(struct student_course));

//                     send(clientSocket, "Enrollment Success\n", strlen("Enrollment Success\n"), 0);
//                 } else {
//                     send(clientSocket, "No available seats\n", strlen("No available seats\n"), 0);
//                 }

//                 break;
//             }
//         }

//         // If the course is not found, send a message to the client
//         if (found_c == 0){
//             send(clientSocket, "Course not found\n", strlen("Course not found\n"), 0);
//         }

//         close(fd);
//     }
// }

void dropCourse(int clientSocket){

    char enroll_course_id[10];
    struct course temp_course;
    char student_id[10];
    char password[10];

     // Prompt for Student ID
    send(clientSocket, "Enter Student ID: ", strlen("Enter Student ID: "), 0);

    // Read Student ID
    int readResult = read(clientSocket, student_id, sizeof(student_id) - 1);
    if (readResult <= 0)
    {
        send(clientSocket, "Error receiving student ID from server", strlen("Error receiving student ID from server"), 0);
        return;
    }
    student_id[readResult] = '\0';

    // Prompt for Student Password
    send(clientSocket, "Enter Student Password: ", strlen("Enter Student Password: "), 0);

    // Read Student Password
    readResult = read(clientSocket,password, sizeof(password) - 1);
    if (readResult <= 0)
    {
        send(clientSocket, "Error receiving student password from server", strlen("Error receiving student password from server"), 0);
        return;
    }
    password[readResult] = '\0';

    send(clientSocket, "Enter Course ID to Drop the course: ", strlen("Enter Course ID to Drop the course: "), 0);
    recv(clientSocket, enroll_course_id, sizeof(enroll_course_id), 0);

    // Check if the student is already enrolled in the course
    int isEnrolled = 0;

    // Open the student_course.txt file for reading
    int studentCourseFile = open("student_course.txt", O_RDWR | O_APPEND | O_CREAT, 0666);
    if (studentCourseFile != -1) {
        struct student_course temp_entry;

        // Loop through the file to check if the student is already enrolled
        while (read(studentCourseFile, &temp_entry, sizeof(struct student_course)) > 0) {
            // Check if the student is already enrolled in the course
            if (strcmp(student_id, temp_entry.student_id) == 0 && strcmp(enroll_course_id, temp_entry.course_id) == 0) {
                isEnrolled = 1;
                break;
            }
        }
    }

    if (!isEnrolled) {
        send(clientSocket, "Student is not enrolled for the course\n", strlen("Student is not enrolled for the course\n"), 0);
        return;
    } else{
    int fd = open("course_database.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        send(clientSocket, "Error unenrolling from course\n", strlen("Error unenrolling from course\n"), 0);
        return;
    }

    int courseFound = 0;

    while (read(fd, &temp_course, sizeof(temp_course)) > 0) {
        if (strcmp(enroll_course_id, temp_course.course_id) == 0) {
            int seat = atoi(temp_course.seats);
            seat++;
            lseek(fd, -sizeof(struct course), SEEK_CUR);
            strncpy(temp_course.seats, intToString(seat), sizeof(temp_course.seats) - 1);
            write(fd, &temp_course, sizeof(temp_course));
            send(clientSocket, "Unenrolled Successfully\n", strlen("Unenrolled Successfully\n"), 0);
            courseFound = 1;
            break;
        }
    }

    if (!courseFound) {
        send(clientSocket, "Course not found\n", strlen("Course not found\n"), 0);
        close(fd);
        return;
    }

    close(fd);


    struct student_course s_c;
    // Open the course database file for reading and writing
    int fd2 = open("student_course.txt", O_RDWR);
    if (fd2 == -1) {
        perror("Error opening file");
        send(clientSocket, "Error enrolling in course\n", strlen("Error enrolling in course\n"), 0);
        return;
    }
    int course_Found = 0;
    while (read(fd2, &s_c, sizeof(s_c)) > 0) {
        if ((strcmp(student_id, s_c.student_id) == 0) && (strcmp(enroll_course_id, s_c.course_id) == 0)) {
            // Found the course, write a null string to course_id field
            lseek(fd2, -sizeof(struct student_course), SEEK_CUR);
            memset(&s_c.course_id, '\0', sizeof(s_c.course_id));
            write(fd2, &s_c, sizeof(s_c));
            course_Found = 1;
            break;
        }
    }
    if (!course_Found) {
        send(clientSocket, "Course not found in catalog\n", strlen("Course not found in catalog\n"), 0);
    } else {
        send(clientSocket, "Course removed from catalog\n", strlen("Course removed from catalog\n"), 0);
    }
    close(fd2);
    }
}

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
            char adminPrompt[] = "\n----------Student Menu----------:\n - 1. View all courses\n - 2. Enroll in a course\n - 3. Drop a coures\n - 4. View Faculty Details\n - 5. Activate Student\n - 6. Block Student\n - 7. Modify Student Details\n - 8. Modify Faculty Details\n - 9. Logout and Exit\n";
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
                    viewAllCourses(clientSocket);
                    break;
            case 2:
                    enrollNewCourse(clientSocket);
                    break;
            case 3:
                    dropCourse(clientSocket);
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