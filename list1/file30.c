/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to run a script at a specific time using a Daemon process.

Date: 4th Sep, 2023.
============================================================================
*/
#include<stdio.h>
#include<sys/stat.h>
#include<time.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
time_t rawtime;
struct tm* timeinfo;

int main(){
	int pid=fork();
	if(pid==-1){
		perror("Error");
		return 1;
	}
	else if(pid)
	{
		printf("Parent Process: %d\n",getpid());
	}
	else 
	{
		printf("Child Process: %d\n",getpid());
		
		int session_id=setsid();
		printf("Session id: %d\n",session_id);
		
		chdir("/");
		umask(0);
		time(&rawtime);
		timeinfo=localtime(&rawtime);
		while(timeinfo->tm_hour <= 23 && timeinfo->tm_min<58)
		{
			sleep(10);
			
			time(&rawtime);
			timeinfo = localtime(&rawtime);
		}
		if(timeinfo->tm_hour == 23 && timeinfo->tm_min==58)
		{
			system("sh home/sample.sh");
			printf("Executed Successfully");
		}
	}
	
}
			
		
