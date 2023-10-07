#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
	int fd[2], n;
	char buffer[100];
	pid_t p;
	pipe(fd);
	p = fork();
	if(p>0)
	{
		write(fd[1], "hello\n", 6);
	}
	else
	{
	}
