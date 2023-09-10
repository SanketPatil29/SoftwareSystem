/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to display the environmental variable of the user (use environ).

Date: 30th Aug, 2023.

============================================================================
*/
#include <stdio.h>

int main()
{
	extern char** environ;
	for(int i=0; environ[i]!=NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}

       
