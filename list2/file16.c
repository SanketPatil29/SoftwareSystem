/*
Name: Sanket S. Patil (MT2023051)
Program to send and receive data from parent to child vice versa, Two way communication.
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main(){
    int pipefd1[2];
    int pipefd2[2];
    char msg1[] = "Parent->Child..Communication\n";
    int p1 = pipe(pipefd1);
    int p2 = pipe(pipefd2);
    if ((p1 == -1) || (p2 == -1)){
        perror("Pipe\n");
        exit(-1);
    }
    char read_buffer[100];
    int c_pid = fork();
    if (!c_pid){
        // Child Sending
        close(pipefd2[0]);
        char msg2[] = "Child->Parent..Communication\n";
        write(pipefd2[1], msg2, strlen(msg2)+1);
        close(pipefd2[1]);

        //Child Received
        int received = read(pipefd1[0], read_buffer, sizeof(read_buffer));
        printf("Child Received: %s\n", read_buffer);
        close(pipefd1[0]);
    }
    else{
        // Parent Writing
        close(pipefd1[0]);
        char msg1[] = "Parent->Child..Communication";
        write(pipefd1[1], msg1, strlen(msg1)+1);
        close(pipefd1[1]);

        //Parent receiving....
        char read_buffer1[100];
        int received = read(pipefd2[0], read_buffer1, sizeof(read_buffer1));
        if (received){
            printf("Parent Received: %s\n", read_buffer1);
            close(pipefd2[0]);
        }
    }
    return 0;
}