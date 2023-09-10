/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to perform Record locking.
 b. Implement read lock
 
Date: 1st Sep, 2023.
============================================================================
*/
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	struct Ticket
	{
	int ticket_no;
	}ticket;
	int fd=open("18.txt", O_RDWR | O_APPEND);
	if(fd==-1)
	{
		perror("error in opening file");
		close(fd);
		return 0;
	}
	struct flock readl;
	int recordID;
	printf("Enter record id you want to lock(read lock): ");
	scanf("%d",&recordID);
	off_t recordoff=(off_t)(sizeof(struct Ticket) * (recordID -1));
	readl.l_type= F_RDLCK;
	readl.l_whence= SEEK_SET;
	readl.l_start=recordoff;
	readl.l_len=sizeof(struct Ticket);
	
	printf("Before Entering into Critical Section \n");
	fcntl(fd, F_SETLKW, &readl);
	printf("You are inside record no %d\n", recordID);
	lseek(fd,(recordID-1)*sizeof(struct Ticket), SEEK_SET);
	ssize_t readb=read(fd, &ticket, sizeof(ticket));
	printf("your ticket no. is %d\n",ticket.ticket_no);
	printf("Inside the Critical Section\n");
	printf("To get Out of Critical Section press any key to Unlock \n");
	getchar();
	getchar();
	
	readl.l_type=F_UNLCK;
	fcntl(fd, F_SETLKW, &readl);
	printf("You are outside the CS and Read Lock is Unlocked\n");
	
	close(fd);
	
	
	
return 0;
}



