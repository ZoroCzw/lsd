#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

/*
 * 不完整管道：写一个读端已经被关闭的管道
 */


void	sig_handler(int signo)
{
	if(signo == SIGPIPE){
		printf("SIGPIPE occured\n");
	}

}

int main(void)
{
	int fd[2];
	if(pipe(fd) < 0){
		perror("pipe error");
		exit(1);
	}

	pid_t	pid;
	pid = fork();
	if(pid < 0){
		perror("fork error");
		exit(1);
	}else if(pid == 0){		//子进程
		//关闭管道的读写端
		close(fd[0]);
		close(fd[1]);
	}else{					//父进程
		sleep(5);
		//从不完整的管道写入数据
		close(fd[0]);
		if(signal(SIGPIPE, sig_handler) == SIG_ERR){
			perror("signal sigpipe error");
			exit(1);
		}
		char *s = "1234";
		if(write(fd[1], s, sizeof(s)) != sizeof(s)){
			fprintf(stderr, "%s, %s\n",strerror(errno), 
				(errno == EPIPE) ? "EPIPE" : "unknow");
		}
		close(fd[1]);
		wait(0);
	}

	exit(0);
}

