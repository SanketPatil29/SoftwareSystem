#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *args[]) {
	if(argc != 2) {
		printf("Expected 2 arguments\n");
		return -1;
	}
	int fd = open(args[1], O_RDWR);
	if(fd == -1) {
		printf("Could not open file\n");
		return -1;
	}
	char buff[] = "abcd";
	int write_res = write(fd, &buff, 10);
	if(write_res == -1) {
		printf("Could not write\n");
		return -1;
	}
	int offset = lseek(fd, 10, SEEK_SET);
	printf("Value of lseek: %d\n", offset);
	write_res = write(fd, &buff, 10);
	close(fd);
	return 0;
}
