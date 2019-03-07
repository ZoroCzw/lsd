#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		fprintf(stderr, 
			"usage: %s file length\n", argv[0]);
		exit(1);
	}

	if(access(argv[1], W_OK) < 0)
	{
		perror("write permission error");
		exit(1);
	}

	//将文件截短为指定长度
	//atoi字符数组转化为整型
	if(truncate(argv[1], atoi(argv[2])) < 0)
	{
		perror("truncate error");
		exit(1);
	}
	int fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		perror("open error");
		exit(1);
	}
	long len = lseek(fd, 0L, SEEK_END);
	printf("file length: %ld\n", len);

	close(fd);
	return 0;
}
