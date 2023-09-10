/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to create a file and print the file descriptor value. Use creat ( ) system call


Output : File name file3_created.txt is created and on concole program prints File descriptor value of the file
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(){
	int fd = creat("File3_created.txt", O_RDONLY | O_WRONLY);
	if (fd == -1){
		perror("Failed to create file");}
	printf("File descritor value for PID: %d is %d\n",getpid(), fd);
	return 0;
}
