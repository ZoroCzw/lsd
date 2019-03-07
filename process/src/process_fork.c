#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int g_v = 30;				//数据段

int main(void)
{
	int a_v = 30;			//栈
	static int s_v =30;		//数据段
	printf("pid: %d\n", getpid());
	
	FILE *fp =fopen("s.txt", "w");
	int fd = open("s_fd.txt",
				O_WRONLY | O_CREAT | O_TRUNC,
							S_IRWXU | S_IRWXG);
	char *s = "hello iotek";
	ssize_t size = strlen(s) * sizeof(char);
	/*父进程调用*/
	//标准IO函数（带缓存-->全缓存）
	fprintf(fp, "s:%s, pid:%d", s, getpid());	//写入缓存（堆）
	//内核提供的IO系统调用（不带缓存）
	write(fd, s, size);    	//直接写入文件

	pid_t pid;
	pid = fork();	//创建子进程
	//在fork之后会运行俩个进程（父进程和子进程）
	if(pid < 0)
	{
		perror("fork error");
	}
	else if(pid > 0)	
	//父进程(父进程fork返回子进程的pid)
	//父进程执行的代码
	{
		g_v = 40; a_v = 40; s_v = 40;
		printf("I am parent process pid is %d,ppid is %d, fork return is %d \n",
				getpid(), getppid(),pid);
		printf("g_v: %p, a_v: %p, s_v: %p \n",
								&g_v, &a_v ,&s_v);
	}
	else				
	//子进程（子进程fork返回的是0）
	//子进程执行的代码
	{
		g_v = 50; a_v = 50; s_v = 50;
		printf("I am child processs pid is %d,ppid is %d, fork return is %d\n",
				getpid(), getppid(), pid);
		printf("g_v: %p, a_v: %p, s_v: %p \n",
								&g_v, &a_v ,&s_v);
	}
	//父子进程都要执行
//	printf("pid: %d, g_v: %d, a_v: %d, s_v: %d\n", 
//				getpid(), g_v, a_v, s_v);
	//父子进程都要执行
	fprintf(fp,"pid: %d, g_v: %d, a_v: %d, s_v: %d\n", 
				getpid(), g_v, a_v, s_v);
	sleep(1);
	
	return 0;


}

