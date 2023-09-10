/*
==========================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to execute ls -Rl by the following system calls
 c. execle

Date: 3rd Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    
    printf("Using execle:\n");
    char *envp[] = { NULL };
    execle("/bin/ls", "ls", "-Rl", NULL, envp);
    
    perror("exec");
    return 1;
}

