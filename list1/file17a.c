#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int fd = open("ticket.txt", O_RDWR);
	struct {
		int ticketNo;
	} data;
	data.ticketNo = 0;
	write(fd, &data, sizeof(data));
	close(fd);
	return 0;
}
