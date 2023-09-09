#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *args[]) {
	if(argc != 2) {
		printf("Invalid number of arguments, expected %d\n", (argc - 1));
		return -1;
	}
	struct stat information;
	int res = stat(args[1], &information);
	if(res == -1) {
		printf("Could not read information of file\n");
		return -1;
	}
	printf("inode: %lu\n", information.st_ino);
	printf("Number of hard links: %lu\n", information.st_nlink);
	printf("uid: %d\n", information.st_uid);
	printf("gid: %d\n", information.st_gid);
	printf("size: %lu\n", information.st_size);
	printf("block size: %lu\n", information.st_blksize);
	printf("number of blocks: %lu\n", information.st_blocks);
	printf("time of last access: %s\n", ctime(&information.st_atime));
	printf("time of last modification: %s\n", ctime(&information.st_mtime));
	printf("time of last change: %s\n", ctime(&information.st_ctime));
	return 0;
}
