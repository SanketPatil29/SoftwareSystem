/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Find out the priority of your running program. Modify the priority with nice command.
 
Date: 1st Sep, 2023.
============================================================================
*/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/resource.h>

int main(){
	int priority;
	priority=getpriority(PRIO_PROCESS,0);
	printf("PID is %d and Current Priority is:%d\n",getpid(),priority);
	getchar();

	nice(10);
	
	priority=getpriority(PRIO_PROCESS,0);
	printf("PID is %d and Current Priority is:%d\n",getpid(),priority);
	getchar();
	return 0;
}

/*

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/resource.h>



int main(){
	int priority=getpriority(PRIO_PROCESS,getpid());
	if(priority==-1){
		perror("Error");
		return 1;
	}
	printf("Current Priority is:%d\n",priority);



	int nice_value=10;
	int pid_new=nice(nice_value);
	if(pid_new==-1){
		perror("nice");
		return 1;
	}
	int priority1=getpriority(PRIO_PROCESS,getpid());

	printf("Nice value : %d\n",priority1);
	return 0;
}

*/
