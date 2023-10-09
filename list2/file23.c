/*
Name: Sanket S. Patil (MT2023051).

Printing maximum number of files can be opened within a process and size of pipe

*/

#include<stdio.h>
#include<limits.h>
#include<unistd.h>

int main(){
    long max_files = sysconf(_SC_OPEN_MAX);
    if(max_files == -1){
        perror("sysconf");
        return 1;
    }

    long pipe_size = sysconf(_PC_PIPE_BUF);
    if(pipe_size == -1){
        perror("sysconf");
        return 1;
    }

    printf("Max #files: %ld\n", max_files);
    printf("Size of pipe: %ld\n", pipe_size);

    return 0;
}