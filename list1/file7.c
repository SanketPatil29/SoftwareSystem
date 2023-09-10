/*
============================================================================

Author : Sanket Shantaram Patil
Roll No : MT2023051
Description : Write a program to copy from one file to other

Date: 28th Aug, 2023.

============================================================================
*/


#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int main(){
	char buff;
	int fd_one, fd_two;
	fd_one = open("./file7.c", O_RDONLY);
	if (fd_one == -1){
		perror("Failed: opening file");}
	fd_two = open("./file7_copied.txt", O_WRONLY | O_CREAT);

	while(read(fd_one, &buff, 1)){
		write(fd_two, &buff, 1);
	}
	printf("Successfully Copied!");
	return 0;
}
