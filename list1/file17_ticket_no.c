/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to simulate online ticket reservation. Implement write lock
Write a program to open a file, store a ticket number and exit. Write a separate program, to
open the file, implement write lock, read the ticket number, increment the number and print
the new ticket number then close the file.
 
Date: 31th Aug, 2023.
============================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main(){
    char s[20];
    int a;
    int fd=open("17.txt", O_RDWR | O_CREAT,0666 );
    printf("Enter the random value for the ticket no");
    scanf("%d",&a);
    
    snprintf(s,sizeof(s),"%d\n",a);
    write(fd,s,strlen(s));
    close(fd);
    return 1;
}
