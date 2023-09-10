/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to create a Zombie state of the running program.

Date: 1st Sep, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	int pid=fork();
	if(pid==0)
	{
		printf("Child Process : %d\n",getpid());
	}
	else{
		sleep(20);
		printf("Parent Process : %d\n",getpid());
	}
}

