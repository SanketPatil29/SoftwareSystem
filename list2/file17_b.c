/*
Name: Sanket S. Patil (MT2023051).
Program to execute ls -l | wc using,
    a. dup
    b. dup2
    c. fcntl
*/

// Using dup2
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
    int pipefd[2];
    pipe(pipefd);
    int c_pid = fork();
    if(!c_pid){
        close(pipefd[0]);
        close(1);
        dup2(pipefd[1], STDOUT_FILENO); 
        execlp("ls", "ls", "-l", (char*)NULL);
    }
    else{
        wait(0);
        close(0);
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO); 
        execlp("wc", "wc", (char*)NULL);
    }
    return 0;
}