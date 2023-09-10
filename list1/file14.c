/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to find the type of a file.
	 a. Input should be taken from command line.
	 b. program should be able to identify any type of a file

Date: 30th Aug, 2023.

============================================================================
*/
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	if(argc != 2){
		printf("Please Enter the filename after ./a.out");
		return 0;
	}
	struct stat filestat;
	if(stat(argv[1],&filestat)==-1)
	{
		perror("error in getting info\n");
		return 0;
	}
	if(S_ISREG(filestat.st_mode)){
	 	printf("Regular file\n");
	}
	else if(S_ISBLK(filestat.st_mode))
	{
		printf("Block device\n");
	}
	else if(S_ISCHR(filestat.st_mode))
	{
		printf("Character device\n");
	}
	else if(S_ISDIR(filestat.st_mode)){
		printf("Directory\n");
	}
	else if(S_ISFIFO(filestat.st_mode)){
		printf("FIFO (named file)\n");
	}
	else if(S_ISLNK(filestat.st_mode)){
		printf("Symbolic link\n");
	}
	else if(S_ISSOCK(filestat.st_mode)){
		printf("Socket\n");
	}
	else
	{
		printf("unknown type\n");
	}
	return 0;
}
