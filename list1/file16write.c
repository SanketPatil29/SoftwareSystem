/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to perform mandatory locking.
 a. Implement write lock
 
Date: 31th Aug, 2023.
============================================================================
*/
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
int main(){
	int fd = open("16.txt", O_RDWR | O_CREAT , 0766);
        if(fd==-1){
		perror("error while opening the file");
		close(fd);
		return 1;
	}
	struct flock writeLock;
	writeLock.l_type=F_WRLCK;
	writeLock.l_whence=SEEK_SET;
	writeLock.l_start=0;
	writeLock.l_len=0;
	
	printf("Write Lock going to apply\n");
	fcntl(fd,F_SETLKW,&writeLock);
	
	printf("Write lock is Locked\n");
	printf("Press any key to Unlock write Lock\n");
	getchar();
	
	writeLock.l_type=F_UNLCK;
	fcntl(fd,F_SETLKW,&writeLock);
	printf("Write Lock is Unlocked");
	
	close(fd);
	return 0;
}
