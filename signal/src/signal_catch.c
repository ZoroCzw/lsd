#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

//定义信号处理函数
//signo: 进程所捕获的信号
void sig_handler(int signo)
{
	printf("%d, %d occrued\n", getpid(), signo);
}

int main(void)
{
	//向内核登记信号处理函数以及信号值
	if(signal(SIGTSTP, sig_handler) == SIG_ERR)
	{
		perror("signal sigtstp error");
	}

	if(signal(SIGINT, sig_handler) == SIG_ERR)
	{
		perror("signal sigint error");
	}

	if(signal(SIGUSR1, sig_handler) == SIG_ERR)
	{
		perror("signal sigusr1 error");
	}
	
	if(signal(SIGUSR2, sig_handler) == SIG_ERR)
	{
		perror("signal sigusr2 error");
	}

	int i = 0;
	while(i < 20)
	{
		printf("%d out %d\n", getpid(), i++);
//		if(i == 10)
//		{
//			kill(getpid(), SIGKILL);
//		}
		sleep(1);
	}
	raise(SIGUSR1);
	kill(getpid(), SIGUSR2);
	return 0;
}

