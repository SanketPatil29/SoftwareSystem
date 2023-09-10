/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to
verify whether the data is available within 10 seconds or not (check in $man 2 select). 

Date: 30th Aug, 2023.

============================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/select.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	fd_set rfds;
	struct timeval tv;
	int retval;
	
	FD_ZERO(&rfds);//initialize all fd's in the fd-set to zeros
	FD_SET(0,&rfds); //add fd=0(stdin) to fd-set by setting corresponding bit to 1
	
	tv.tv_sec=10;
	tv.tv_usec=0;
	retval=select(1,&rfds,NULL,NULL,&tv);
	
	if(retval)
		printf("Data is available within 10 sec\n");
	else
		printf("Data is not availablewithin 10 sec\n");
}
