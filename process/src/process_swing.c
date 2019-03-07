#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int counter = 0;
	if(argc < 2)
	{
		counter = 2;
	}
	else
		counter = atoi(argv[1]);
	
	int i = 1;
	pid_t pid;
	for( ; i < counter; i++)
	{
		pid = fork();
		if(pid < 0)
		{
			perror("fork error");
			exit(1);
		}
		else if(pid == 0) break;
		//父进程退出循环，子进程继续做循环
	}
	printf("pid: %d, ppid : %d, pgid: %d\n", 
					getpid(), getppid(), getpgid(0));
	while(1)
	{
		sleep(2);
	}

	return 0;

}
