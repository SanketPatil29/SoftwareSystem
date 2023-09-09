#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void readFile(char *file) {
	int fd_read = open(file, O_RDONLY);
	while(1) {
		char buffer;
		int size = read(fd_read, &buffer, 1);
		if(size == 0) {
			break;
		}
		printf("%c", buffer);
	}
}

int using_dup(char *file) {
	int original_fd = open(file, O_RDWR);
	if(original_fd == -1) {
		printf("Could not open file\n");
		return -1;
	}
	// Duplicate fd
	int dup_fd = dup(original_fd);
	if(dup_fd == -1) {
		printf("Could not duplicate using dup()\n");
		return -1;
	}
	// Write and read using original descriptor
	char original_buff[] = "original fd\n";
	int original_write = write(original_fd, &original_buff, sizeof(original_buff));
	readFile(file);
	printf("\n");
	// Write and read using duplicate descriptor
	char dup_buff[] = "dup buff\n";
	int dup_write = write(dup_fd, &dup_buff, sizeof(dup_buff));
	readFile(file);

	// Close fd's 
	close(original_fd);
	close(dup_fd);
}

int using_dup2(char *file) {
	int original_fd = open(file, O_RDWR);
	if(original_fd == -1) {
		printf("Could not open file\n");
		return -1;
	}
	int dup_fd = dup2(original_fd, 5);
	if(dup_fd == -1) {
		printf("Could not duplicate using dup()\n");
		return -1;
	}
	char original_buff[] = "original fd\n";
	int original_write = write(original_fd, &original_buff, sizeof(original_buff));
	readFile(file);
	printf("\n");
	// Write and read using duplicate descriptor
	char dup_buff[] = "dup buff\n";
	int dup_write = write(dup_fd, &dup_buff, sizeof(dup_buff));
	readFile(file);

	// Close fd's 
	close(original_fd);
	close(dup_fd);
}

int using_fcntl(char *file) {
	int original_fd = open(file, O_RDWR);
	if(original_fd == -1) {
		printf("Could not open file\n");
		return -1;
	}
	int dup_fd = fcntl(original_fd, F_DUPFD);
	if(dup_fd == -1) {
		printf("Could not duplicate using dup()\n");
		return -1;
	}
	// Write and read using original descriptor
	char original_buff[] = "original fd\n";
	int original_write = write(original_fd, &original_buff, sizeof(original_buff));
	readFile(file);
	printf("\n");
	// Write and read using duplicate descriptor
	char dup_buff[] = "dup buff\n";
	int dup_write = write(dup_fd, &dup_buff, sizeof(dup_buff));
	readFile(file);

	// Close fd's 
	close(original_fd);
	close(dup_fd);
}

int main(int argc, char *args[]) {
	if(argc != 2) {
		printf("Expected 1 argument\n");
		return -1;
	}
	using_dup(args[1]);
	using_dup2(args[1]);
	using_fcntl(args[1]);
	return 0;
}
