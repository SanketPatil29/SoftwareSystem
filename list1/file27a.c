/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a pragram to execute ls -Rl by the following system calls
 a. execl

Date: 3rd Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    printf("Using execl:\n");
    execl("/bin/ls", "ls", "-Rl", NULL);
    
    perror("exec");
    return 1;
}

