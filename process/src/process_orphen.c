#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	pid = fork();
	if(pid < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if(pid > 0)
	{
		printf("%d deaded\n", getpid());
		exit(0);
	}
	else
	{
		sleep(4);
		printf("pid: %d, ppid: %d", 
					getpid(), getppid());
	}
	return 0;
}

