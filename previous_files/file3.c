#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

int main()
{
	int fd = creat("a.txt", O_RDONLY | O_WRONLY | O_RDWR);
	printf("fd = %d\n", fd);
	int fd1 = creat("b.txt", O_RDONLY | O_WRONLY | O_RDWR);
	printf("fd1 = %d\n", fd1);
	return 0;
}
