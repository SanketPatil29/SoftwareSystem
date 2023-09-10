/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. 
Check output of the file

Date: 1st Sep, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	int fd=open("22.txt",O_CREAT | O_RDWR,0666);
	if(fd==-1){
		perror("Error in opening the file");
		return 1;
	}

	int pid=fork();
	if(pid){
		char s[27]="Hello I am Parent \n";
		write(fd,&s,sizeof(s));			
	}
	else if(pid==0){	
		char s[25]="Hello I am child process\n";
		write(fd,&s,sizeof(s));
	}
	else{ 
		printf("Error");
	}
	close(fd);
	return 1;
}
