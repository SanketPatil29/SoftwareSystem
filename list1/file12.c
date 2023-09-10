/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to find out the opening mode of a file. Use fcntl. 

Date: 29th Aug, 2023.

============================================================================
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Enter file name as well after %s\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR);    
    if (fd == -1) {
        perror("Error while  opening file");
        return 1;
    }

    int flag = fcntl(fd, F_GETFL);
    if (flag == -1) {
        perror("Error... not getting file access mode");
        close(fd);
        return 1;
    }

    if ((O_ACCMODE & flag)==O_RDONLY) {
        printf("File is opened in read-only mode\n");
    } else if ((O_ACCMODE & flag)==O_WRONLY) {
        printf("File is opened in write-only mode\n");
    } else if ((O_ACCMODE & flag)==O_RDWR) {
        printf("File is opened in read-write mode\n");
    } else {
        printf("Unable to determine file access mode\n");
    }

    close(fd);

    return 0;
}

