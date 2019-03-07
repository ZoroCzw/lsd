#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler(int signo)
{
	if(signo == SIGINT)
	{
		printf("\nprocess the SIGINT\n");
		sleep(5);
		printf("ppid: %d ,%d catch SIGINT\n", getppid(), getpid());
		printf("process the SIGINT finished\n");
	}
	if(signo == SIGTSTP)
	{
		printf("\nprocess the SIGSTP\n");
		sleep(5);
		printf("%d catch SIGSTP\n", getpid());
		printf("process the SIGSTP finished\n");
	}
}

int main(void)
{
	if(signal(SIGINT, sig_handler) == SIG_ERR)
	{
		perror("signal sigint error");
	}
	if(signal(SIGTSTP, sig_handler) == SIG_ERR)
	{
		perror("signal sigstop error");
	}

	printf("begin running\n");
	while(1) pause();	//等待信号
	printf("end running");
}

