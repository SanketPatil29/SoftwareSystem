#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(){
	int res;
	res = mkfifo("FIFO", 0777);
	if(res<0)
		perror("Failed to create pipe\n");
	return 0;
}


