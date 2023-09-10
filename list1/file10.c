/*
============================================================================

Author : Sanket Shantaram Patil
Roll No : MT2023051
Description : Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10
	bytes (use lseek) and write again 10 bytes.
 	a. check the return value of lseek
 	b. open the file with od and check the empty spaces in between the data. 

Date: 30th Aug, 2023.

============================================================================
*/


#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc, char *args[]){
	if(argc != 2){
		printf("Excepted 2 arguments\n");
		return -1;
	}
	int fd = open(args[1], O_RDWR);
	if (fd == -1){
		printf("Could not open file\n");
		return -1;
	}
	char buff[] = "abcd";
	int write_res = write(fd, &buff, 10);
	if(write_res == -1){
		printf("Could not write\n");
 		return -1;
	}
	int offset = lseek(fd, 10, SEEK_CUR);
	printf("Value of lseek: %d\n", offset);
	write_res = write(fd, &buff, 10);
	close(fd);
	return 0;
}

		
