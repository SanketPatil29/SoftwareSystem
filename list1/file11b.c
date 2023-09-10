/*
============================================================================

Author : Sanket Patil
Roll No : MT2023051
Description : Write a program to open a file, duplicate the file descriptor and append the file with both the
descriptors and check whether the file is updated properly or not.
b. use dup2

Date: 28th Aug, 2023.

============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main(){
	int fdold = open("11.txt", O_WRONLY|O_CREAT|O_APPEND,0666);  
    	if(fdold == -1){
		printf("Error while opening the file\n");
		close(fdold);
		return 1;
    	}   
    
    	int fdnew = dup2(fdold,5);
    	if(fdnew == -1){
		printf("Error while opening the file\n");
		close(fdnew);
		return 1;
   	}  
	
	//printf("%d\n",fdold);
	//printf("%d\n",fdnew);
	
	char s[25];
    	snprintf(s,sizeof(s),"File Descriptor fold: %d\n",fdold);
    	write(fdold,s, sizeof(s));
    
    	snprintf(s,sizeof(s),"File Descriptor fnew: %d\n",fdnew);
    	write(fdnew,s, strlen(s));
      
    	close(fdold);
    	close(fdnew); 
        return 0;
}
