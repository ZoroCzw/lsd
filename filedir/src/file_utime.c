#include <time.h>
#include <utime.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>

struct stat get_stat(char *file, struct stat buff)
{
	memset(&buff, 0, sizeof(buff));
	if(lstat(file, &buff) < 0)
	{
		perror("lstat error");
		exit(1);
	}
	return buff;
}

void out(struct stat buff)
{
	printf("atime: %s", ctime(&buff.st_atime));
	printf("mtime: %s", ctime(&buff.st_mtime));
	printf("ctime: %s", ctime(&buff.st_ctime));
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "usage: %s file\n", argv[0]);
		exit(1);
	}
	struct stat buff;
	buff = get_stat(argv[1], buff);
	//备份原先的时间
	struct stat back = buff;
	out(buff);
	printf("--------------------------\n");
	//设置文件的时间为当前系统时间
	utime(argv[1], NULL);
	buff = get_stat(argv[1], buff);
	out(buff);
	printf("--------------------------\n");

	//将文件时间恢复为原先时间
	struct utimbuf timebuf;
	timebuf.actime = back.st_atime;
	timebuf.modtime = back.st_mtime;
	utime(argv[1], &timebuf);
	buff = get_stat(argv[1], buff);
	out(buff);

	return 0;
}
