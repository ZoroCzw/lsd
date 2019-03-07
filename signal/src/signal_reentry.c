#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int g_v[10];
int *h_v;

void set(int val)
{
	int a_v[10];
	int i = 0;
	
	for(; i < 10; i++)
	{
		a_v[i] = val;
		g_v[i] = val;
		h_v[i] = val;
		sleep(1);
	}

	printf("g_v:");
	for(i = 0; i < 10; i++)
	{
		if(i != 0)
			printf(", %d", g_v[i]);
		else
			printf("%d", g_v[i]);
	}
	printf("\n");

	printf("h_v:");
	for(i = 0; i < 10; i++)
	{
		if(i != 0)
			printf(", %d", h_v[i]);
		else
			printf("%d", h_v[i]);
	}
	printf("\n");

	printf("a_v:");
	for(i = 0; i < 10; i++)
	{
		if(i != 0)
			printf(", %d", a_v[i]);
		else
			printf("%d", a_v[i]);
	}
	printf("\n");
}

void sig_handler(int signo)
{
	if(signo == SIGTSTP)
	{
		printf("SIGTSTP occured\n");
		set(20);
		printf("end SIGTSTP\n");
	}
}

int main(void)
{
	if(signal(SIGTSTP, sig_handler) == SIG_ERR)
	{
		perror("signal sigtstp error");
	}
	
	h_v = (int*)calloc(10, sizeof(int));

	printf("begin running main\n");
	set(10);
	printf("end running main\n");

	return 0;
}

