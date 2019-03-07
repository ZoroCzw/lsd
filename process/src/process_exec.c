#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
char *cmd1 = "cat";	//相对路径
char *cmd2 = "/bin/cat";	//绝对路径
char *argv1 = "/etc/passwd";
char *argv2 = "/etc/group";

int main()
{
	pid_t pid;
	if((pid = fork()) < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if(pid == 0)
	{
	//错误的，cmd1必须为绝对路径
	//	if(execl(cmd1, cmd1, argv1, argv2, NULL) < 0)
		if(execl(cmd2, cmd2, argv1, argv2, NULL) < 0)
		{
			perror("execl error");
			exit(1);
		}
		else
		{
			printf("execl %s success \n", cmd1);
		}
	}
	wait(NULL);		//wait(0);
	
	printf("---------------------------------------\n");
	
	if((pid = fork()) < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if(pid == 0)
	{
		char *argv[4] = {cmd1, argv1, argv2, NULL};
		if(execvp(cmd1, argv) < 0)
		{
			perror("execvp error");
			exit(1);
		}
		else
		{
			printf("execvp %s success \n", cmd1);
		}
	}
	wait(NULL);
	return 0;
}

