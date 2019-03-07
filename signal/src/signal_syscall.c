#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sig_handler(int signo)
{
	if(signo == SIGTSTP)
	{
		printf("SIGTSTP occured \n");
	}
}

int main(void)
{
	char buffer[512];
	ssize_t size;
	if(signal(SIGTSTP, sig_handler) == SIG_ERR)
	{
		perror("signal sigtstp error");
	}
	
	printf("begin running and waiting for signal\n");
	size = read(STDIN_FILENO, buffer, 512);
	if(size < 0)
	{
		perror("read error");
	}
	printf("reading finished\n");
	if(write(STDOUT_FILENO, buffer, size) != size)
	{
		perror("write error");
	}
	printf("end runnning\n");

	return 0;
}



