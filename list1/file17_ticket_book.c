/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to simulate online ticket reservation. Implement write lock
Write a program to open a file, store a ticket number and exit. Write a separate program, to
open the file, implement write lock, read the ticket number, increment the number and print
the new ticket number then close the file.
 
Date: 31th Aug, 2023.
============================================================================
*/
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int main(){
	int fd = open("17.txt", O_RDWR, 0666);
        if(fd==-1){
		perror("Error while opening the file");
		close(fd);
		return 1;
	}
	
	struct flock writeLock;
	writeLock.l_type=F_WRLCK;
	writeLock.l_whence=SEEK_SET;
	writeLock.l_start=0;
	writeLock.l_len=0;
	
	printf("Before Entering into Critical Section \n");
	fcntl(fd,F_SETLKW,&writeLock);
	
	char ticketno[20];
	char *output;
	read(fd,&ticketno,sizeof(ticketno));
	long i=strtol(ticketno,&output,10);

	i++;
	char s[20];
	snprintf(s,sizeof(s),"%ld\n",i);
	printf("Current Ticket No is: %ld\n",i);
	lseek(fd,0L,SEEK_SET);
        write(fd,s,strlen(s));
	//write(fd,&ticketno,sizeof(ticketno));
	
	printf("Inside the Critical Section\n");
	printf("To get Out of Critical Section press any key to Unlock \n");
	getchar();
	writeLock.l_type=F_UNLCK;
	fcntl(fd,F_SETLKW,&writeLock);
	printf("You are outside the CS and Write Lock is Unlocked\n");
	
	close(fd);
	return 0;
}
