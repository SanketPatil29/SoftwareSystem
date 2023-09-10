/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program, call fork and print the parent and child process id.
 
Date: 1st Sep, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
int main(){
	int pid=fork();
	if(pid == -1){
		printf("Fork Failed");
		return 1;
	}
	else if(pid){
		printf("Parent pid : %d\n",getpid());
		//printf("Child pid : %d\n",pid);
	}
	else if(pid==0){
		printf("child pid : %d\n",getpid());
	}
}
