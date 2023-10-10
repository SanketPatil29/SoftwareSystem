/*
Name: Sanket S. Patil (MT2023051).
Two programs communicating through FIFO (One way communication)
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
    int fd;
    char buff[100] = "program 1 msg";
    fd = open("file20", O_WRONLY);
    write(fd, buff, sizeof(buff));
    close(fd);
    return 0;
}