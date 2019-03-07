#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define MODE S_IRWXU | S_IRWXG | S_IRWXO
#define UMASK S_IXUSR | S_IWGRP | S_IXGRP | S_IRWXO

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "usage: %s file\n", argv[0]);
		exit(1);
	}

	//设置掩码，仅仅与当前进程相关
	/*
	umask(UMASK);
	int fd = open(argv[1],
		O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, MODE);
	if(fd < 0)
	{
		perror("open error");
		exit(1);
	}
	*/
	int fd = open(argv[1], O_RDWR);
	if(fd < 0)
	{
		perror("open error");
		exit(1);
	}
	fchmod(fd, MODE);
	close(fd);
	return 0;
}

