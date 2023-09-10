/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to execute ls -Rl by the following system calls
 b. execlp

Date: 3rd Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    
    printf("Using execlp:\n");
    execlp("ls", "ls", "-Rl", NULL);
    
    perror("exec");
    return 1;
}

