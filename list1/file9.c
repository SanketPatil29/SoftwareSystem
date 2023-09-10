/*
============================================================================

Author : Sanket Shantaram Patil
Roll No : MT2023051
Description : Write a program to print the following information about a given file.
 a. inode
 b. number of hard links
 c. uid
 d. gid
 e. size
 f. block size
 g. number of blocks
 h. time of last access
 i. time of last modification
 j. time of last change

============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char *args[]){
	struct stat information;
	int res = stat(args[1], &information);
	if(res == -1){
		printf("Could not read information of file\n");
		return -1;
	}
	printf("INODE: %lu\n", information.st_ino);
	printf("#Hard_links: %lu\n", information.st_nlink);
	printf("uid: %d\n", information.st_uid);
	printf("gid: %d\n", information.st_gid);
	printf("size: %lu\n", information.st_size);
	printf("Block Size: %lu\n", information.st_blksize);
	printf("#Blocks: %lu", information.st_blocks);
	printf("Last access time: %s\n", ctime(&information.st_atime));
	printf("Last modification time: %s\n", ctime(&information.st_mtime));
	printf("Last change time: %s\n", ctime(&information.st_ctime));

	return 0;
}

	
