#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
int main(void)
{
	//创建进程组，组长进程为父进程
	setpgid(getpid(), getpid());
	pid_t group1 = getpgid(getpid());
	pid_t group2;

	int i = 0;
	pid_t pid;
	for(i; i < 3; i++)
	{	
		pid = fork();
		if(pid < 0)
		{
			perror("fork error");
		}
		else if(pid > 0)
		{
			if(i == 0)
			{
				setpgid(pid, group1);
			}
			else if(i == 1)
			{
			//第二个子进程创建组，第二个子进程作为组长进程
				setpgid(pid, pid);
				group2 = getpgid(pid);
			}
			else if(i == 2)
			{
			//第三个子进程加入group2
				setpgid(pid, group2);
			}
		}
		else
		{
			//将第一个子进程加入都group1当中
			if(i == 0)
			{
				setpgid(getpid(), group1);
			}
			else if(i == 1)
			{
				setpgid(getpid(), getpid());
				group2 = getpgid(getpid());
			}
			else if(i == 2)
			{
				setpgid(getpid(), group2);
			}
			break;
		}
	}
	printf("pid:%d, ppid: %d, pgid: %d\n",
			getpid(), getppid(), getpgid(0));
	for(i = 0; i < 3;i++)
	{
		wait(NULL);
	}
	exit(0);
}
