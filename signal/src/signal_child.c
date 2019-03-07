#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void sig_handler(int signo)
{
	printf("%d child process deaded, signo: %d\n", getpid(),signo);
	wait(0);
}
void out(int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		printf("%d out %d\n", getpid(), i);
		sleep(2);
	}
}
int main(void)
{
	if(signal(SIGCHLD, sig_handler) == SIG_ERR)
	{
		perror("signal child error");
	}
	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if(pid > 0)
	{//父进程
		out(100);
	}
	else
	{//子进程
		out(10);
	}

	return 0;
}

