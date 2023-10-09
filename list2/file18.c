/*
Name: Sanket S. Patil (MT2023051).
    Executing ls -l | grep ^d | wc using dup2()
*/

// Using dup2
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
    int pipefd1[2];
    int pipefd2[2];
    pipe(pipefd1);
    pipe(pipefd2);
    int c_pid1, c_pid2;
    c_pid1 = fork();
    c_pid2 = fork();

    if(!c_pid1){
        dup2(pipefd1[1], STDOUT_FILENO); 
        close(pipefd1[0]);
        close(pipefd2[0]);
        close(pipefd2[1]);
        execlp("ls", "ls", "-l", (char*)NULL);
    }
    else{

        if(c_pid2){
            dup2(pipefd2[1], 1);
            dup2(pipefd1[0], 0);
            close(pipefd1[1]);
            close(pipefd2[0]);
            execlp("grep", "grep", "^d", (char*) NULL);
         }
        else{
            waitpid(c_pid1, NULL, WNOHANG);
            waitpid(c_pid2, NULL, WNOHANG);
            dup2(pipefd2[0], STDIN_FILENO);
            close(pipefd2[1]);
            close(pipefd1[0]);
            close(pipefd1[1]);
            execlp("wc", "wc", (char*)NULL);
        }
    }
    return 0;
}