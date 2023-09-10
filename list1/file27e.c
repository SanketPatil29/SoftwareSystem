/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to execute ls -Rl by the following system calls
 e. execvp

Date: 3rd Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    
    char *args[] = { "ls", "-Rl", NULL };
    printf("Using execvp:\n");
    execvp("ls", args);
 
    perror("exec");
    return 1;
}


	
