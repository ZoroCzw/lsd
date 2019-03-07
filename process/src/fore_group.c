#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t group1, group2;

	setpgid(getpid(), getpid());
	group1 = getpgid(getpid());

	pid_t pid;
	int i = 0;
	for(; i< 3; i++)
	{
		pid = fork();
		if(pid < 0)
		{
			perror("fork error");
			exit(1);
		}
		else if(pid > 0)	//parent process
		{
			if(i == 0)
			{
				//创建进程组
				setpgid(pid, pid);
				group2 = getpgid(pid);
			}
			else if(i == 1)
			{
				//第二个子进程加入到group2
				setpgid(pid, group2);
				//将group2设置为前台进程组
				tcsetpgrp(0, group2);
			}
			else if(i == 2)
			{
				//将第三个子进程加入到group1
				setpgid(pid, group1);
			}
		}
		else
		{
			if(i == 0)
			{
				setpgid(getpid(), getpid());
				group2 = getpgid(getpid());
			}
			else if(i == 1)
			{
				setpgid(getpid(), group2);
				tcsetpgrp(0, group2);
			}
			else if(i == 2)
			{
				setpgid(getpid(), group1);
			}
			break;
		}
	}
	printf("pid: %d, ppid: %d, pgid: %d\n",
				getpid(), getppid(), getpgid(0));
	pause();

	return 0;
}
