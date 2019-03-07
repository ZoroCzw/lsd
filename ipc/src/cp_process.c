#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
	int fda[2], fdb[2];

	//创建俩个管道
	if((pipe(fda) < 0) || (pipe(fdb) < 0)){
		perror("pipe error");
		exit(1);
	}

	pid_t	pid;
	pid = fork();
	if(pid < 0){
		perror("fork error");
		exit(1);
	}else if(pid == 0){		//子进程
		/*
		 * 1）子进程负责从管道a中读取父进程写入的累加参数x和y
		 * 2）通过exec函数去调用bin/add程序进程累加
		 * 3）将累加结果写入到管道b
		 */
		close(fda[1]);
		close(fdb[0]);
		//标准输入重定向到管道a的读端
		if(dup2(fda[0], STDIN_FILENO) != STDIN_FILENO){
			perror("dup2 error");
		}
		//标准输出重定向到管道b的写端
		if(dup2(fdb[1], STDOUT_FILENO) != STDOUT_FILENO){
			perror("dup2 error");
		}

		close(fda[0]);
		close(fdb[1]);

		if(execlp("bin/add", "bin/add", NULL) < 0){
			perror("execlp error");
			exit(1);
		}

	}else{					//父进程
	 	/*
		 * 1）从标准输入上读取累加参数x和y
		 * 2）将x和y写入管道a
		 * 3）从管道b中读取累加的结果并输出
		 */
		close(fda[0]);
		close(fdb[1]);
		printf("please input x, y:\n");
		int x, y;
		//if(read(STDIN_FILENO, &x, sizeof(int)) < 0){
		//	perror("read error");
		//}
		//if(read(STDIN_FILENO, &y, sizeof(int)) < 0){
		//	perror("read error");
		//}
		scanf("%d  %d", &x, &y);
		//x = 5, y = 10; 
		printf("x = %d, y = %d\n", x, y);
		if(write(fda[1], &x, sizeof(int)) 
								!= sizeof(int)){
			perror("write error");						
		}
		if(write(fda[1], &y, sizeof(int)) 
								!= sizeof(int)){
			perror("write error");						
		}
		int result = x + y;
		if(read(fdb[0], &result, sizeof(int))
								!= sizeof(int)){
			perror("read error");					
		}else{
			printf("add result is %d\n", result);
		}
		close(fda[1]);
		close(fdb[0]);
		wait(0);
	
	}




	return 0;
}

