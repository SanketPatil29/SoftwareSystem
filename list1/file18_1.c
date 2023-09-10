/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to perform Record locking.
Create three records in a file. Whenever you access a particular record, first lock it then modify/access
to avoid race condition.
 
Date: 1st Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	struct ticket
	{
	 int ticket_no;
	};
	struct ticket t[3];
	int fd= open("18.txt", O_RDWR | O_CREAT, 0666);
       if(fd==-1)
       {
		perror("error in opening file");
       }
       for(int i=0;i<3;i++)
       {
	       printf("Enter the random value for the ticket no for record %d : ",i+1);
	       scanf("%d" ,&t[i].ticket_no);
	       write(fd, &t[i], sizeof(struct ticket));
       }
     
        
       	return 0;
}
