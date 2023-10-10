/*
Name: Sanket S. Patil (MT2023051).
Two programs communicating through FIFO (One way communication)
*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    char read_buff[100];
    int fd = open("file20", O_RDONLY);
    read(fd, read_buff, sizeof(read_buff));
    printf("Msg: %s\n", read_buff);
    close(fd);
    return 0;
}