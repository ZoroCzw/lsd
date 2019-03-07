#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	//创建进程组，父进程作为组长
	setpgid(getpid(), getpid());

	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if(pid > 0)
	{	//parent process
		//将子进程加入到父进程所在组
		setpgid(pid, getpgid(getpid()));
	}
	else
	{	//child process
	 	//将子进程加入到父进程所在组
		setpgid(getpid(), getpgid(getppid()));
	}
	
	printf("pid: %d, ppid: %d, pgid: %d\n",
				getpid(), getppid(), getpgid(0));
	
	pause();

	exit(0);
}
