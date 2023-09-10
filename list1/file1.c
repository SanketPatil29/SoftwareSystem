/*
============================================================================
Author : Sanket Patil
Roll No : MT2023051
Description : Create the following types of a files using (i) shell command (ii) system call
 	a. soft link (symlink system call)
 	b. hard link (link system call)
 	c. FIFO (mkfifo Library Function or mknod system call)

Date: 21th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
	int s_link = symlink("temp.txt", "s_link");
	int h_link = link("temp.txt", "h_link");
	if( s_link < 0 || h_link < 0){
		perror("Failed");
		return 1;
	}
	printf("Links created\n");
	return 0;
}
