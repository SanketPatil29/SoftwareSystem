#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    int pipefd[2];
    int child_pid;
    
    char msg[] = "Hello, Child!";

    if (pipe(pipefd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    child_pid = fork();
    if (child_pid == 0){
        close(pipefd[1]); // write end closed

        char buffer[100];
        int bytes_read = read(pipefd[0], buffer, sizeof(buffer));

        if (bytes_read>0){
            buffer[bytes_read] = '\0';
            printf("Child received: %s\n", buffer);
        }
        close(pipefd[0]);
    }
    else{
        close(pipefd[0]);
        write(pipefd[1], msg, strlen(msg)+1);
        close(pipefd[1]);
    }
    return 0;
}