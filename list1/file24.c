/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to create an orphan process.

Date: 2nd Sep, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main(){
	int pid=fork();
	if(pid==0){
		sleep(10);
		printf("I am a Child Process : %d\n",getpid());
		printf("My Parent Process id is: %d\n",getppid());
	}
	else{
		sleep(5);
		printf("I am Parent Process : %d\n",getpid());
		printf("My child process id is :%d\n",pid);
	}
}
