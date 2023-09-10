/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to create five new files with infinite loop. Execute the program in the background
and check the file descriptor table at /proc/pid/fd 


Date: 25th Aug, 2023.
Output : run command: ls -l /proc/processid/fd
============================================================================
*/


#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(){

	int fd1 = creat("f51.txt", O_RDONLY);
	int fd2 = creat("f52.txt", O_RDONLY);
	int fd3 = creat("f53.txt", O_RDONLY);
	int fd4 = creat("f54.txt", O_RDONLY);
	int fd5 = creat("f55.txt", O_RDONLY);
	//printf("FDs: %d %d %d %d %d\n",fd1, fd2, fd3, fd4, fd5);
	//printf("%d\n", getpid());
	while(1);
}

