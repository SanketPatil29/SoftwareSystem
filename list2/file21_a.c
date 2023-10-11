/*
Name: Sanket S. Patil (MT2023051).
Two programs communicating through FIFO (Two way communication)
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
    int fd1, fd2;
    
    fd1 = open("fifo21_a", O_RDONLY);
    if(fd1 == -1){
        perror("Open fifoA");
        exit(EXIT_FAILURE);
    }
    fd2 = open("fifo21_b", O_WRONLY);
    if(fd2 == -1){
        perror("Open fifo_b");
        close(fd1);
        exit(EXIT_FAILURE);
    }
    char buff1[100]; 
    char buff2[100];
    
    printf("Enter Message: ");
    scanf("%[^\n]", buff1);
    //Write to fifo 1
    write(fd1, buff1, sizeof(buff1));
    //Read from fifo 2
    read(fd2, buff2, sizeof(buff2));
    printf("msg: %s\n", buff2);

    close(fd1);
    close(fd2);

    return 0;
}