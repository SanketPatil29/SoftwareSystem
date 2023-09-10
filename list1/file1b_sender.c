#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
	int res,n;
	res = open("FIFO", O_WRONLY);
	//res = open("FIFO", O_NONBLOCK, O_WRONLY); same for receiver to run without sender too
	
	write(res, "Message", 7);
	printf("Sender process pid: %d\n", getpid());
}

