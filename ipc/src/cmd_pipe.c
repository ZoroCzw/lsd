#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

char *cmd1[3] = {"/bin/cat", "/etc/passwd", NULL};
char *cmd2[3] = {"/bin/grep", "root", NULL};


int main(void)
{
	int fd[2];
	if(pipe(fd) < 0){
		perror("pipe error");
		exit(1);
	}
	int i = 0;
	
	pid_t	pid;
	
	for(; i < 2; i++){
		pid = fork();	
		if(pid < 0){
			perror("fork error");
			exit(1);
		}else if(pid == 0){		//子进程
			if(i == 0){			
				//第一个子进程，写入数据
				//关闭读端
				close(fd[0]);
				//将标准输出重定向到管道的写端
				//dup2(int oldfd, int newfd);
				if(dup2(fd[1], STDOUT_FILENO) 
								!=STDOUT_FILENO ){
					perror("dup2 error");
					exit(1);
				}
				close(fd[1]);
				//调用exec执行cat
				if(execvp(cmd1[0], cmd1) < 0){
					perror("execvp error");
					exit(1);
				}
				
				break;
			}
			if(i == 1){			
				//第二个子进程，读取数据
				//关闭写端
				close(fd[1]);
				
				if(dup2(fd[0], STDIN_FILENO)
							  	!= STDIN_FILENO){
					perror("dup2 error");
					exit(1);
				}
				close(fd[0]);

				//调用exec函数执行grep
				if(execlp(cmd2[0], "/bin/cat", "root", NULL) < 0){
					perror("execvp error");
				}
				break;
			}
		}else{					//父进程
			if(i == 1){
				//子进程全部创建完毕
				close(fd[0]);
				close(fd[1]);
				wait(0);
				wait(0);
			}
		}
	}

	exit(0);
}

