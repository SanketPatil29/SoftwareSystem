#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *args[]) {
	int fd_read = open(args[1], O_RDONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
	int fd_write = open(args[2], O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if(argc != 3) {
		printf("Incorrect argument count, must have 3\n");
		return -1;
	}
	if(fd_read == -1 || fd_write == -1) {
		printf("Could not open file %d %d\n", fd_read, fd_write);
		return -1;
	}
	while(1) {
		char buffer;
		int size = read(fd_read, &buffer, 1);
		if(size == 0) {
			break;
		}
		int res = write(fd_write, &buffer, size);
	}
	int fd_read_close = close(fd_read);
	int fd_write_close = close(fd_write);
	if(fd_read_close == -1 || fd_write_close == -1) {
		printf("Could not close files\n");
	}
	return 0;
}
