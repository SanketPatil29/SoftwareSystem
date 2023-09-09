#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main()
{
	while(1){
		creat("f1.txt", O_RDWR);
		creat("f2.txt", O_RDWR);
		creat("f3.txt", O_RDWR);
		creat("f4.txt", O_RDWR);
		creat("f5.txt", O_RDWR);
		sleep(10);
	}
	return 0;
}

