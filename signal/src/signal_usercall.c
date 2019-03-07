#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void sig_handler(int signo)
{
	if(signo == SIGTSTP)
	{
		printf("SIGTSTP occured\n");
	}
}

void call_fun(void)
{
	printf("begin running call_fun\n");
	sleep(10);
	printf("end running call_fun\n");
}

int main(void)
{
	if(signal(SIGTSTP, sig_handler) == SIG_ERR)
	{
		perror("signal sigtstp error");
	}

	printf("begin running main\n");
	call_fun();
	printf("end running main\n");

	return 0;
}

