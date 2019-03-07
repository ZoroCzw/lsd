#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(void)
{
	printf("pid: %d\n", getpid());				//当前启动进程id
	printf("ppid: %d\n", getppid());			//当前进程父进程id
	printf("uid: %d\n", getuid());				//当前实际用户id
	printf("euid: %d\n", geteuid());			//当前有效用户id
	printf("user gid: %d\n", getgid());			//获得用户组id
	printf("gid: %d\n", getpgrp());				//获得进程组id
	printf("pgid: %d\n", getpgid(getpid()));	//获得指定进程所在进程组id
	printf("ppgid: %d\n", getpgid(getppid()));	//获得当前父进程所在进程组id
}

