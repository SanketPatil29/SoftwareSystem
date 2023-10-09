/*
Name: Sanket S. Patil (MT2023051).
Creating FIFO file by:
    a. mknode command
    b. mkfifo command
    c. mknode system call
    d. mkfifo library function
*/

// Using mknod
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main(){
    char * buff = "Helllooo!";
    char r_buff[100];
    int fifo = mknod("file19_fifo2", S_IFIFO | 0666, 0);
    int fd = open("file19_fifo2", O_RDWR);
    write(fd, buff, sizeof(buff));
    read(fd, r_buff, sizeof(buff));
    printf("Text: %s", r_buff);
    return 0;
}