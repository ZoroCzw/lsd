#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("current pid: %d\n", getpid());
	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fork error");
	}
	else if(pid > 0)
	//parent process
	{
		int i;
		for(i = 0; i < 10; i++)
		{
			printf("This is parent process pid is: %d\n",
					getpid());
			sleep(1);
		}
	}
	else
	//child process
	{
		int i;
		for(i = 0; i < 10; i++)
		{
			printf("This is child process pid is: %d\n",
					getpid());
			sleep(1);
		}
	}


	return 0;
}
