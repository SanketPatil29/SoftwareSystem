#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

int main() {
	fd_set stdin_set;
	struct timeval timelimit;
	FD_ZERO(&stdin_set);
	FD_SET(0, &stdin_set);
	
	timelimit.tv_sec = 10;
	
	int res = select(1, &stdin_set, NULL, NULL, &timelimit);
	if(res) {
		printf("Data is available\n");
	}
	else {
		printf("No data available\n");
	}
	return 0;
}
