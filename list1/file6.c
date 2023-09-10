/*
============================================================================

Author : Sanket Shantaram Patil
Roll No : MT2023051
Description : Write a program to take input from STDIN and display on STDOUT. Use only read/write system call 


Date: 26th Aug, 2023.
============================================================================
*/


#include<stdio.h>
#include<unistd.h>
//#include<sys/types.h>
//#include<sys/types.h>
int main(){
	char buff[10];
	read(0, &buff, 10);
	write(1, &buff, 10);
	return 0;
}

