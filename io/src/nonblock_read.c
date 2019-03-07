#include "io.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
	char buffer[4096] = {'\0'};
	ssize_t size = 0;

	set_fl(STDIN_FILENO, O_NONBLOCK);
	
	sleep(5);
	
	size = read(STDIN_FILENO, buffer, sizeof(buffer));
	if(size < 0)
	{
		perror("read error");
		exit(1);
	}
	else if(size == 0)
	{
		printf("read finished\n");
	}
	else
	{
		if(write(STDOUT_FILENO, buffer, size) != size)
		{
			perror("write error");
			exit(1);
		}
	}

}

