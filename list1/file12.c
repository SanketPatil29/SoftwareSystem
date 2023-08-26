#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *args[]) {
	if(argc != 2) {
		printf("Expected 1 argument\n");
		return -1;
	}
	int fd = open(args[1], O_RDWR);
	int access_mode = fcntl(fd, F_GETFL);
	printf("access mode: %d\n", access_mode);
	close(fd);
	return 0;
}
