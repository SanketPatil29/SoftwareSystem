#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

struct data {
	int val;
};

int main() {
	int fd = open("record.txt", O_WRONLY);
	struct data r1, r2, r3;
	r1.val = 1;
	r2.val = 2;
	r3.val = 3;
	write(fd, &r1, sizeof(r1));
	write(fd, &r2, sizeof(r2));
	write(fd, &r3, sizeof(r3));
	close(fd);
	return 0;
} 
