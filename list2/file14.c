/*
 * Name: Sanket S. Patil
 * Roll No: MT2023051
 * Simple program to create a pipe, write to the pipe,   read from pipe and display on the monitor.
*/
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    int pipefd[2];

    if (pipe(pipefd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    char msg[] = "Communicating through pipe....";
    
    write(pipefd[1], msg, strlen(msg)+1);
    printf("msg Written to the pipe.\n");
    close(pipefd[1]);

    char buffer[100];

    // Reading the pipe's content.
    read(pipefd[0], buffer, sizeof(buffer));
    close(pipefd[0]);
    printf("Pipe's msg: %s\n", buffer);
    return 0;
}
