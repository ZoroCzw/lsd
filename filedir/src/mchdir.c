#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
#include <memory.h>

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "usage: %s\n", argv[0]);
		exit(1);
	}
	
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	//获得当前工作目录
	if(getcwd(buff, sizeof(buff)) != NULL)
	{
		printf("current dir: %s\n", buff);
	}
	//切换目录
	if(chdir(argv[1]) < 0)
	{
		perror("chdir error");
		exit(1);
	}
	//获得切换后的新目录
	if(getcwd(buff, sizeof(buff)) != NULL)
	{
		printf("current dir: %s\n", buff);
	}

	return 0;
}
