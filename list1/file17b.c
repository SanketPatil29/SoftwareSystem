#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

struct data {
	int ticketNo;
};

int main() {
	int fd = open("ticket.txt", O_RDWR);
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	printf("Acquiring lock\n");
	fcntl(fd, F_SETLKW, &lock);
	printf("Lock acquired, incrementing ticket\n");
	struct data ticketInformation;
	read(fd, &ticketInformation, sizeof(ticketInformation));
	printf("Previous ticket number: %d\n", ticketInformation.ticketNo);
	ticketInformation.ticketNo++;
	printf("Current ticket number: %d\n", ticketInformation.ticketNo);
	lseek(fd, 0L, SEEK_SET);
	write(fd, &ticketInformation, sizeof(ticketInformation));
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	printf("Lock release\n");
	return 0;
}
