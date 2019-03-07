#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int is_sig_occ = 0;

void sig_handler(int signo)
{
	printf("signo occured: %d\n", signo);
	is_sig_occ = 1;
	printf("I will running\n");
}

int main(void)
{
	if(signal(SIGINT, sig_handler) == SIG_ERR)
	{
		perror("signal sigint error");
	}
	printf("begin running\n");
	while(is_sig_occ == 0)
	{
		sleep(5);
		pause();
	}
	//依赖于信号执行的代码
//	printf("I will running\n");

	return 0;
}

