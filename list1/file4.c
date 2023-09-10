/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to open an existing file with read write mode. Try O_EXCL flag also. 

============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(){
	int fd = open("temp.txt",O_EXCL, O_RDWR);
	if (fd == -1)
		perror("Failed");
	else
		printf("File opened with FD Val: ");
	printf("%d", fd);
	return 0;
}

