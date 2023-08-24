#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#define FNAME "file4.txt"

int main(){

	int filedes;
	filedes = open(FNAME, O_EXCL, O_RDWR);

	if(filedes == -1){
		perror("Failed");
	}
	else{
		printf("File opened");
	}
	printf("%d\n", filedes);
	return 0;

}
