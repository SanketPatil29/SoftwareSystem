// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <arpa/inet.h>
// #include <pthread.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <signal.h>
// #include <error.h>


// #define PORT 8080
// #define MAX_BUFFER_SIZE 1024

// // Define user roles
// #define ROLE_ADMIN 1
// #define ROLE_FACULTY 2
// #define ROLE_STUDENT 3

// // Sample user accounts
// struct User {
//     char username[50];
//     char password[50];
//     int role;
// };

// struct User users[] = {
//     {"admin", "adminpass"},
//     {"faculty", "facultypass"},
//     {"student", "studentpass"}
// };

// int authenticate_user(char *username, char *password, int *role) {
//     int i = *role - 1;
//     if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
//         return 1; // Authentication success
//     }

//     return 0; // Authentication failure
// }

// void *handle_client(void *socket_desc) {
//     int client_socket = *(int *)socket_desc;
//     char buffer[MAX_BUFFER_SIZE] = {0};
//     const char *response = "Hello from server!";

//     // Authentication
//     char username[50];
//     char password[50];
//     int role;

//     // read(client_socket, &role, sizeof(int));
//     read(client_socket, username, sizeof(username));
//     read(client_socket, password, sizeof(password));
    

//     if (!authenticate_user(username, password, &role)) {
//         const char *auth_fail_msg = "Authentication failed. Exiting...";
//         send(client_socket, auth_fail_msg, strlen(auth_fail_msg), 0);
//         close(client_socket);
//         free(socket_desc);
//         pthread_exit(NULL);
//     }

//     const char *auth_success_msg = "Authentication successful!";
//     send(client_socket, auth_success_msg, strlen(auth_success_msg), 0);

//     // Read from the client
//     read(client_socket, buffer, MAX_BUFFER_SIZE);
//     printf("Client (%s): %s\n", username, buffer);

//     // Send a response to the client
//     send(client_socket, response, strlen(response), 0);
//     printf("Response sent to the client.\n");

//     // Close the socket and exit the thread
//     close(client_socket);
//     free(socket_desc);
//     pthread_exit(NULL);
// }

// int main() {
//     int server_fd, new_socket;
//     struct sockaddr_in address;
//     int addrlen = sizeof(address);
//     pthread_t thread;

//     // Creating socket file descriptor
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//         perror("Socket creation failed");
//         exit(EXIT_FAILURE);
//     }

//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(PORT);

//     // Forcefully attaching socket to the port 8080
//     if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
//         perror("Bind failed");
//         exit(EXIT_FAILURE);
//     }

//     if (listen(server_fd, 3) < 0) {
//         perror("Listen failed");
//         exit(EXIT_FAILURE);
//     }

//     printf(" %d...\n", PORT);

//     while (1) {
//         // Authentication
//         char username[50];
//         char password[50];
//         int role;

//         if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
//             perror("Accept failed");
//             exit(EXIT_FAILURE);
//         }

//         // read(new_socket, &role, sizeof(int));
//         read(new_socket, username, sizeof(username));
//         read(new_socket, password, sizeof(password));

//         if (!authenticate_user(username, password, &role)) {
//             const char *auth_fail_msg = "Authentication failed. Exiting...";
//             send(new_socket, auth_fail_msg, strlen(auth_fail_msg), 0);
//             close(new_socket);
//             continue;
//         }

//         const char *auth_success_msg = "Authentication successful!";
//         send(new_socket, auth_success_msg, strlen(auth_success_msg), 0);

//         int *client_socket = malloc(sizeof(int));
//         *client_socket = new_socket;

//         // Create a new thread to handle the client
//         if (pthread_create(&thread, NULL, handle_client, (void *)client_socket) < 0) {
//             perror("Thread creation failed");
//             exit(EXIT_FAILURE);
//         }

//         // Detach the thread to avoid memory leaks
//         pthread_detach(thread);
//     }

//     return 0;
// }

















// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <arpa/inet.h>

// #define PORT 8080
// #define MAX_BUFFER_SIZE 1024

// void display_menu() {
//     printf("Select login type:\n");
//     printf("1. Admin\n");
//     printf("2. Faculty\n");
//     printf("3. Student\n");
// }

// int main() {
//     int sock = 0;
//     int choice;
//     struct sockaddr_in serv_addr;
//     char buffer[MAX_BUFFER_SIZE] = {0};
//     char username[50], password[50];
//     const char *message = "Hello from client!";

//     display_menu();
//     printf("Enter your choice: ");
//     scanf("%d", &choice);

//     // Get username and password from user
//     printf("Enter username: ");
//     scanf("%s", username);
//     printf("Enter password: ");
//     scanf("%s", password);

//     // Creating socket file descriptor
//     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//         perror("Socket creation error");
//         return -1;
//     }

//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_port = htons(PORT);

//     // Convert IPv4 and IPv6 addresses from text to binary form
//     if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
//         perror("Invalid address/ Address not supported");
//         return -1;
//     }

//     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
//         perror("Connection Failed");
//         return -1;
//     }

//     // Send username and password to the server for authentication
//     // send(sock, choice, sizeof(choice), 0);
//     send(sock, username, strlen(username), 0);
//     send(sock, password, strlen(password), 0);


//     // Receive authentication result from the server
//     recv(sock, buffer, MAX_BUFFER_SIZE, 0);
//     printf("%s\n", buffer);

//     if (strcmp(buffer, "Authentication successful!") != 0) {
//         // Authentication failed, exit the program
//         close(sock);
//         return -1;
//     }

//     // Authentication successful, proceed with communication
//     // Send a message to the server
//     send(sock, message, strlen(message), 0);
//     printf("Message sent to the server.\n");

//     // Read the response from the server
//     read(sock, buffer, MAX_BUFFER_SIZE);
//     printf("Server: %s\n", buffer);

//     // Close the socket
//     close(sock);

//     return 0;
// }


// fork()











int viewFaculty1(int clientSocket) {
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

    // Read faculty details from the file and send to the client
    struct faculty faculty_info;
    ssize_t bytesRead;
    while ((bytesRead = read(fd, &faculty_info, sizeof(struct faculty))) > 0) {
        char facultyDetailsBuffer[1024];
        snprintf(facultyDetailsBuffer, sizeof(facultyDetailsBuffer), "ID: %s\nName: %s\nDepartment: %s\nEmail: %s\nDesignation: %s\n\n",
                 faculty_info.faculty_id, faculty_info.name, faculty_info.dept, faculty_info.email, faculty_info.designation);
        send(clientSocket, facultyDetailsBuffer, strlen(facultyDetailsBuffer), 0);
    }

    flock(fd, LOCK_UN); // Release the lock
    close(fd);          // Close the file

    return 0;
}