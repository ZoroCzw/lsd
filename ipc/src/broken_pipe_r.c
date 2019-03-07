#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

/*
 * 不完整管道：读取一个写端已经关闭的管道
 */


int main(void)
{
	int fd[2];
	if(pipe(fd) < 0){
		perror("pipe error");
		exit(1);
	}
	
	pid_t	pid;
	if((pid = fork()) < 0) {
		perror("fork error");
		exit(1);
	}else if(pid > 0){	//父进程
		//父进程从不完整管道读取数据（写端关闭）
		sleep(5);	//等子进程将管道的写端关闭
		close(fd[1]);
		while(1){
			char c;
			if(read(fd[0], &c, 1) == 0){
				printf("\nwrite-end of pipe closed\n");
				break;
			}else{
				printf("%c", c);
			}
		}
		close(fd[0]);
		wait(0);
	}else{			    //子进程
		close(fd[0]);
		char *s = "1234";
		write(fd[1], s, sizeof(s));
		//写入数据后关闭管道的写端
		close(fd[1]);
	}

	exit(0);
}

