/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to create three child processes. The parent should wait for a particular child (use
waitpid system call).

Date: 3rd Sep, 2023.

============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <stdlib.h>
int main(){
	int pid,pid1,pid2;
	int status;
	pid=fork();
	if(pid==0){
		//sleep(3);
		printf("First Child Process id is : %d\n",getpid());
		printf("Parent of First Child Process id is : %d\n",getppid());
		printf("\n");
	}
	else if(pid > 0){
		pid1=fork();
		if(pid1 == 0){
			//sleep(1);
			printf("Second Child Process id is : %d\n",getpid());
			printf("Parent of Second Child Process id is : %d\n",getppid());
			printf("\n");
		}
		else if(pid1 > 0){
			pid2=fork();
			if(pid2==0){
				sleep(5);
				printf("Third Child Process id is : %d\n",getpid());
				printf("Parent of Third Child Process id is : %d\n",getppid());
				printf("\n");
			}
			else if(pid2 > 0){
				int w = waitpid(pid2,NULL,0);
				printf("waitpid returns = %d\n",w);
				printf("Parent Process id is : %d\n",getpid());
			}
			
		}
	}

	
}

