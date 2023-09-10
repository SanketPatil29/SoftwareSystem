/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to execute ls -Rl by the following system calls
 d. execv

Date: 3rd Sep, 2023.

============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() { 

    printf("Using execv:\n");
    char *args[] = { "ls", "-Rl", NULL };
    execv("/bin/ls", args);
    
    perror("exec");
    return 1;
}

