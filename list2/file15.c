#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(){
	pid_t child_pid;
	int fd;
	char msg[] = "Hellooo, Child!";

	// File is created
	fd = open("file15_msg.txt", O_CREAT | O_RDWR, 0666);
	if(fd == -1){
		perror("Opening file");
		exit(EXIT_FAILURE);
	}

	child_pid = fork();

	if (child_pid == -1){
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0){
		struct flock lock;
		//memset(&lock, 0, sizeof(lock);
		lock.l_type = F_RDLCK;
		fcntl(fd, F_SETLKW, &lock);

		// Read
		char buffer[100];
		int bytes_read = read(fd, buffer, sizeof(buffer));
		if(bytes_read > 0){
			printf("Child received: %s", buffer);
		}

		// Lock released
		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLKW, &lock);

		close(fd);
	}
	else{
		// Parent
		struct flock lock;
		// memeset(&lock, 0, sizeof(lock));
		lock.l_type = F_WRLCK;
		fcntl(fd, F_SETLKW, &lock);
			
		//Write
		printf("Parent is writing\n");
		write(fd, msg, strlen(msg));

		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		close(fd);
	}
	return 0;
}

