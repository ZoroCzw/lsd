#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	setpgid(getpid(), getpid());
	pid_t group1 = getpgid(getpid());

	pid_t pid;

	int i = 0;
	for(; i< 2; i++)
	{
		pid = fork();
		if(pid < 0)
		{
			perror("fork error");
			exit(1);
		}
		else if(pid > 0)
		{
			//在进程链中，父进程操作完退出循环
			if(i == 0)
			{
				//创建进程组2,第一个子进程作为组长
				setpgid(pid, pid);
			}
			else if(i == 1)
			{
				setpgid(pid, group1);
			}
			break;
		}
		else
		{
			if(i == 0)
			{
				setpgid(getpid(), getpid());
			}
			else if(i == 1)
			{
				setpgid(getpid(), group1);
			}
		}
	}

	printf("pid: %d, ppid: %d, pgid: %d \n",
				getpid(), getppid(), getpgid(0));

	sleep(1);

	return 0;
}
