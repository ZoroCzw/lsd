#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "usage: %s file\n", argv[0]);
		exit(1);
	}

	int fd = open(argv[1], O_WRONLY);
	if(fd < 2)
	{
		perror("open error");
		exit(1);
	}
	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fork error");
		exit(1);
	}	
	else if(pid > 0)
	{//父进程将文件偏移量调节到文件尾部
		if(lseek(fd, 0L, SEEK_END) < 0)
		{
			perror("lseek error");
			exit(1);
		}
	}
	else
	{//子进程从尾部追加内容
		char *str = "hello child\n";
		ssize_t size = strlen(str) * sizeof(char);
		sleep(3);
		//此处的fd都是从父进程中复制过来的
		//但是和父进程中的fd都是指向同一个文件
		if(write(fd, str , size) != size)
		{
			perror("write error");
			exit(1);
		}
	}
	printf("pid: %d finish\n", getpid());
	sleep(1);
	//父子进程都要去关闭文件描述符
	
	close(fd);

	return 0;
}
