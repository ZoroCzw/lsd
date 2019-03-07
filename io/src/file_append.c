#include "io.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		printf("uasge: %s content destfile\n", argv[0]);
		exit(1);
	}
	int fd = open(argv[2], O_WRONLY);
	set_fl(fd, O_APPEND);
	/*
	int fd = open(argv[2], O_WRONLY | O_APPEND);
	if(fd < 0)
	{
		perror("open error");
		exit(1);
	}

	lseek(fd, 0L, SEEK_END);
	*/
	sleep(10);
	
	size_t size = strlen(argv[1]) * sizeof(char);
	if(write(fd, argv[1], size) != size)
	{
		perror("write error");
		exit(1);
	}

	close(fd);

	return 0;
}

