/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to perform mandatory locking.
 b. Implement read lock

Date: 30th Aug, 2023.

============================================================================
*/
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
int main(){
	int fd = open("16.txt", O_RDWR | O_CREAT , 0666);
        if(fd==-1){
		perror("error while opening the file");
		close(fd);
		return 1;
	}
	struct flock readLock;
	readLock.l_type=F_RDLCK;
	readLock.l_whence=SEEK_SET;
	readLock.l_start=0;
	readLock.l_len=0;
	
	printf("Read Lock going to apply\n");
	fcntl(fd,F_SETLKW,&readLock);
	
	printf("Read lock is Locked\n");
	printf("Press any key to Unlock read Lock\n");
	getchar();
	
	readLock.l_type=F_UNLCK;
	fcntl(fd,F_SETLKW,&readLock);
	printf("Read Lock is Unlocked");
	
	close(fd);
	return 0;
}
