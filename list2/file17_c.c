/*
Name: Sanket S. Patil (MT2023051).
Program to execute ls -l | wc using,
    a. dup
    b. dup2
    c. fcntl
*/

// Using fcntl

#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    int pipefd[2];
    pipe(pipefd);
    int c_pid = fork();
    if(!c_pid){
        close(pipefd[0]);
        close(1);
        fcntl(pipefd[1], F_DUPFD ,STDOUT_FILENO); 
        execlp("ls", "ls", "-l", (char*)NULL);
    }
    else{
        wait(0);
        close(0);
        close(pipefd[1]);
        fcntl(pipefd[0], F_DUPFD ,STDIN_FILENO);; // fd2== 0 = STDIN
        execlp("wc", "wc", (char*)NULL);
    }
    return 0;
}