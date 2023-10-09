/*
Name: Sanket S. Patil (MT2023051).
Program to execute ls -l | wc using,
    a. dup
    b. dup2
    c. fcntl
*/

// Using dup

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
        int fd1 = dup(pipefd[1]); // fd1 == 1 - STDOUT
        execlp("ls", "ls", "-l", (char*)NULL);
    }
    else{
        wait(0);
        close(0);
        close(pipefd[1]);
        int fd2 = dup(pipefd[0]); // fd2== 0 = STDIN
        execlp("wc", "wc", (char*)NULL);
    }
    return 0;
}