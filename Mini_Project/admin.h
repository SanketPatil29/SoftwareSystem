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

int addFaculty(int clientSocket) {
    struct faculty faculty_info;

    // Client will enter the faculty ID
    send(clientSocket, "Enter the ID of the faculty you want to add\n", strlen("Enter the ID of the faculty you want to add\n"), 0);
    int bytesRead = recv(clientSocket, faculty_info.faculty_id, sizeof(faculty_info.faculty_id), 0);
    if (bytesRead <= 0) {
        perror("Error while receiving faculty ID");
        return 1;
    }
    faculty_info.faculty_id[bytesRead] = '\0';

    // Client will enter the faculty password
    send(clientSocket, "Enter password: ", strlen("Enter password: "), 0);
    bytesRead = recv(clientSocket, faculty_info.password, sizeof(faculty_info.password), 0);
    if (bytesRead <= 0) {
        perror("Error while receiving faculty ID");
        return 1;
    }
    faculty_info.password[bytesRead] = '\0';

    // Client will enter the faculty name
    send(clientSocket, "Enter Name: ", strlen("Enter Name: "), 0);
    bytesRead = recv(clientSocket, faculty_info.name, sizeof(faculty_info.name), 0);
    if (bytesRead <= 0) {
        perror("Error while receiving faculty name");
        return 1;
    }
    faculty_info.name[bytesRead] = '\0';

    // Client will enter the faculty department
    send(clientSocket, "Enter the Department of the faculty you want to add\n", strlen("Enter the Department of the faculty you want to add\n"), 0);
    bytesRead = recv(clientSocket, faculty_info.dept, sizeof(faculty_info.dept), 0);
    if (bytesRead <= 0) {
        perror("Error while receiving faculty department\n");
        return 1;
    }
    faculty_info.dept[bytesRead] = '\0';

    // Client will enter the faculty email
    send(clientSocket, "Enter the Email of the faculty you want to add\n", strlen("Enter the Email of the faculty you want to add\n"), 0);
    bytesRead = recv(clientSocket, faculty_info.email, sizeof(faculty_info.email), 0);
    if (bytesRead <= 0) {
        perror("Error while receiving faculty email\n");
        return 1;
    }
    faculty_info.email[bytesRead] = '\0';

    // Client will enter the faculty designation
    send(clientSocket, "Enter the designation of the faculty you want to add\n", strlen("Enter the designation of the faculty you want to add\n"), 0);
    bytesRead = recv(clientSocket, faculty_info.designation, sizeof(faculty_info.designation), 0);
    if (bytesRead <= 0) {
        perror("Error while receiving faculty email\n");
        return 1;
    }
    faculty_info.designation[bytesRead] = '\0';

    // Open the file to enter this data in the database
    int fd = open("faculty_database.txt", O_WRONLY | O_APPEND | O_CREAT, 0666); // Open the file in append mode

    if (fd == -1) {
        perror("Error opening the file\n");
        close(fd);
        return 1;
    }

    // Use flock to apply mandatory lock
    if (flock(fd, LOCK_EX) == -1) {
        perror("Error applying lock");
        close(fd);
        return 1;
    }

    // Use lseek to move the file pointer to the end of the file
    if (lseek(fd, 0, SEEK_END) == -1) {
        perror("Error using lseek");
        flock(fd, LOCK_UN); // Release the lock before closing the file
        close(fd);
        return 1;
    }

    // Write the structure data to the file
    if (write(fd, &faculty_info, sizeof(struct faculty)) == -1) {
        perror("Error writing to the file");
        flock(fd, LOCK_UN); // Release the lock before closing the file
        close(fd);
        return 1;
    }

    flock(fd, LOCK_UN); // Release the lock
    close(fd);          // Close the file

    return 0;
}


int viewFaculty(int clientSocket) {
    // Ask the client for a faculty ID
    send(clientSocket, "Enter login ID of faculty: ", strlen("Enter login ID of faculty: "), 0);

    // Receive the faculty ID from the client
    char facultyId[11];
    ssize_t bytesRead = recv(clientSocket, facultyId, sizeof(facultyId), 0);
    if (bytesRead <= 0) {
        perror("Error receiving faculty ID");
        send(clientSocket, "Error receiving faculty ID\n", strlen("Error receiving faculty ID\n"), 0);
        return 1;
    }
    facultyId[bytesRead] = '\0'; // Null-terminate the received faculty ID

    // Open the file to read faculty details from the database
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
        if (strcmp(faculty_info.faculty_id, facultyId) == 0) {
            // Found the faculty with the specified ID, send details to the client
            char facultyDetailsBuffer[1024];
            snprintf(facultyDetailsBuffer, sizeof(facultyDetailsBuffer), "ID: %s\nName: %s\nDepartment: %s\nEmail: %s\nDesignation: %s\npass: %s\n",
                     faculty_info.faculty_id, faculty_info.name, faculty_info.dept, faculty_info.email, faculty_info.designation, faculty_info.password);
            send(clientSocket, facultyDetailsBuffer, strlen(facultyDetailsBuffer), 0);
            facultyFound = 1;
            break;
        }
    }

    if (!facultyFound) {
        send(clientSocket, "Faculty not found with the specified ID\n", strlen("Faculty not found with the specified ID\n"), 0);
    }

    flock(fd, LOCK_UN); // Release the lock
    close(fd);          // Close the file

    return 0;
}



// void generateSequentialStudentLoginID(int *lastID, char *loginID) {
//     (*lastID)++; // Increment the last three digits

//     // Format the login ID as "ST2023XXX"
//     snprintf(loginID, 11, "ST2023%03d", *lastID);
// }

int addStudent(int clientSocket) {
    struct student stud_info;

    // Name
    send(clientSocket, "Enter name: ", strlen("Enter name: "), 0);
    int bytesRead = recv(clientSocket, stud_info.name, sizeof(stud_info.name), 0);
    if (bytesRead <= 0) {
        perror("Error while receiving Name\n");
        return false;
    }
    stud_info.name[bytesRead] = '\0';

    // Student ID
    send(clientSocket, "Enter the Student-ID: ", strlen("Enter the Student-ID: "), 0);
    bytesRead = recv(clientSocket, stud_info.student_id, sizeof(stud_info.student_id), 0);
    if (bytesRead <= 0) {
        perror("Error while receiving student ID");
        return 1;
    }
    stud_info.student_id[bytesRead] = '\0';

    // Password
    send(clientSocket, "Enter password: ", strlen("Enter password: "), 0);
    bytesRead = recv(clientSocket, stud_info.password, sizeof(stud_info.password), 0);
    if (bytesRead <= 0) {
        perror("Error while receiving student password\n");
        return 1;
    }
    stud_info.password[bytesRead] = '\0';

    // Department
    send(clientSocket, "Enter the Department: ", strlen("Enter the Department: "), 0);
    bytesRead = recv(clientSocket, stud_info.dept, sizeof(stud_info.dept), 0);
    if (bytesRead <= 0) {
        perror("Error while receiving student department\n");
        return 1;
    }
    stud_info.dept[bytesRead] = '\0';

    // Address
    send(clientSocket, "Enter Address: ", strlen("Enter Address: "), 0);
    bytesRead = recv(clientSocket, stud_info.address, sizeof(stud_info.address), 0);
    if (bytesRead <= 0) {
        perror("Error while receiving student address\n");
        return 1;
    }
    stud_info.address[bytesRead] = '\0';

    // Email
    send(clientSocket, "Enter the Email: ", strlen("Enter the Email: "), 0);
    bytesRead = recv(clientSocket, stud_info.email, sizeof(stud_info.email), 0);
    if (bytesRead <= 0) {
        perror("Error while receiving student email\n");
        return 1;
    }
    stud_info.email[bytesRead] = '\0';

    // Generate sequential login ID for student
    // int lastID = 500; // Initialize with the last used ID (you may load it from a file or database)
    // generateSequentialStudentLoginID(&lastID, stud_info.login_id);

    // ... (previous code)

    // Open the file to enter this data in the database
    int fd = open("student_database.txt", O_WRONLY | O_APPEND | O_CREAT, 0666); // Open the file in append mode

    if (fd == -1) {
        perror("Error opening the file\n");
        close(fd);
        return 1;
    }

    // Use flock to apply mandatory lock
    if (flock(fd, LOCK_EX) == -1) {
        perror("Error applying lock");
        close(fd);
        return 1;
    }

    // Use lseek to move the file pointer to the end of the file
    if (lseek(fd, 0, SEEK_END) == -1) {
        perror("Error using lseek");
        flock(fd, LOCK_UN); // Release the lock before closing the file
        close(fd);
        return 1;
    }

    // Write the structure data to the file
    if (write(fd, &stud_info, sizeof(struct student)) == -1) {
        perror("Error writing to the file");
        flock(fd, LOCK_UN); // Release the lock before closing the file
        close(fd);
        return 1;
    }
    flock(fd, LOCK_UN); // Release the lock
    close(fd);          // Close the file
    return 0;
}


int viewStudent(int clientSocket) {
    // Ask the client for a faculty ID
    send(clientSocket, "Enter login ID of student:\n", strlen("Enter login ID of student:\n"), 0);

    // Receive the faculty ID from the client
    char studentID[11];
    ssize_t bytesRead = recv(clientSocket,studentID , sizeof(studentID), 0);
    if (bytesRead <= 0) {
        perror("Error receiving faculty ID");
        send(clientSocket, "Error receiving student ID\n", strlen("Error receiving student ID\n"), 0);
        return 1;
    }
    studentID[bytesRead] = '\0'; // Null-terminate the received faculty ID

    // Open the file to read faculty details from the database
    int fd = open("student_database.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening the file\n");
        close(fd);
        send(clientSocket, "Error reading student details\n", strlen("Error reading student details\n"), 0);
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
    struct student student_info;
    ssize_t SFound = 0;

    while (read(fd, &student_info, sizeof(struct student)) > 0) {
        if (strcmp(student_info.student_id, studentID) == 0) {
            // Found the faculty with the specified ID, send details to the client
            char studentDetailsBuffer[1024];
            snprintf(studentDetailsBuffer, sizeof(studentDetailsBuffer), "Name: %s\nDepartment: %s\nEmail: %sAddress: %s\n\nID: %s\n",
                    student_info.name, student_info.dept, student_info.email, student_info.address, student_info.student_id);
            send(clientSocket, studentDetailsBuffer, strlen(studentDetailsBuffer), 0);
            SFound = 1;
            break;
        }
    }

    if (!SFound) {
        char* s_notFound = "student not found with the specified ID\n";
        send(clientSocket, s_notFound, strlen(s_notFound), 0);
    }

    flock(fd, LOCK_UN);
    close(fd);          

    return 0;
}

int authenticateAdmin(int clientSocket)
{
    char username[100];
    char pass[100];

    // Send a prompt for the username
    const char *userPrompt = "Enter Admin-ID: ";
    send(clientSocket, userPrompt, strlen(userPrompt), 0);

    // Receive the username from the client
    ssize_t bytesRead = recv(clientSocket, username, sizeof(username), 0);
    if(bytesRead <= 0)
    {
        close(clientSocket);
        return false;
    }
    if(username[bytesRead - 1] == '\n')
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

    // Compare the received username and password with stored credentials
    if (strcmp(username, adminCredentials.admin_id) == 0 &&
        strcmp(pass, adminCredentials.pass) == 0)
    {
        // Authentication successful
        char * success_msg = "login successfully\n"; ///
        send(clientSocket, success_msg, strlen(success_msg), 0);
        return true;
    }
    else
    {
        // Authentication failed
        char * failure_msg = "Authentication failed\n"; ///
        send(clientSocket, failure_msg, strlen(failure_msg), 0);
        close(clientSocket);
        return false;
    }
}



int admin_functionality(int clientSocket) 
{
    if (authenticateAdmin(clientSocket)) // Authenticated successfully.
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
                    addStudent(clientSocket);
                    break;
            case 2:
                    viewStudent(clientSocket);
                    break;
            case 3:
                    addFaculty(clientSocket);
                    break;
            case 4:
                    viewFaculty(clientSocket);
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