#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <signal.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include "msg.h"
int sockfd;

void sig_handler(int signo)
{
	if(signo == SIGINT){
		printf("server close\n");
		/*步骤6：关闭socket*/
		close(sockfd);
		exit(1);
	}
}

/*输出连接上来的客户端相关信息*/
void out_addr(struct sockaddr_in *clientaddr)
{
	//将端口从网络字节序换成主机字节序
	int port = ntohs(clientaddr->sin_port);
	char ip[16];
	memset(ip, 0, sizeof(ip));
	//将ip地址从网络字节序转换成点分十进制
	inet_ntop(AF_INET,
		&clientaddr->sin_addr.s_addr, ip, sizeof(ip));
	printf("client: %s(%d) connected\n", ip, port);
}

/*服务程序*/
void do_service(int fd)
{
	/*和客户端进行双向通信*/
	char buff[512];
	while(1){
		memset(buff, 0, sizeof(buff));
		printf("start read and write...\n");
		size_t size;
		if((size = read_msg(fd, 
				buff, sizeof(buff))) < 0){
			perror("protocal error");
			break;
		}else if(size == 0){
			printf("size==0\n");
			break;
		}else{
			printf("%s\n", buff);
			if(write_msg(fd, buff, sizeof(buff)) < 0){
				if(errno == EPIPE){
					break;
				}
				perror("protocal error");
			}
		}
	}
}
void out_fd(int fd)
{
	struct sockaddr_in addr;
	socklen_t	len = sizeof(addr);
	//从fd中获得客户端的相关信息
	if(getpeername(fd, 
			(struct sockaddr*)&addr, &len) < 0){
		perror("getpeername error");
		return;
	}
	char ip[16];
	memset(ip, 0, sizeof(ip));
	int port = ntohs(addr.sin_port);
	inet_ntop(AF_INET, &addr.sin_addr.s_addr, ip, sizeof(ip));
	printf("%16s(%5d) closed!\n", ip, port);
}
void*	th_fn(void *arg)
{
	int fd = (int)arg;
	do_service(fd);
	out_fd(fd);
	close(fd);
	return (void*)0;
}

int main(int argc, char *argv[])
{
	if(argc < 2){
		printf("usage: %s #port\n", argv[0]);
	}
	if(signal(SIGINT, sig_handler) == SIG_ERR){
		perror("signale sigint error");
		exit(1);
	}

	/* 步骤1：创建socket（套接字）
	 * 注：socket创建在内核中，是一个结构体
	 * AF_INET: IPV4
	 * SOCK_STREAM: tcp协议
	 */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);	
	/*
	 * 步骤2： 调用bind函数将socket和地址
	 *         （包括ip和port）进行绑定
	 */
	struct sockaddr_in 	serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	//往地址中填入ip、port、internet地址族类型
	serveraddr.sin_family = AF_INET; //IPV4
	serveraddr.sin_port = htons(atoi(argv[1]));
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	if(bind(sockfd, (struct sockaddr*)&serveraddr,
							sizeof(serveraddr)) < 0){
		perror("bind error");
		exit(1);
	}
	/*
	 * 步骤3：调用listen函数启动监听(指定port监听)
	 * 		  通知系统去接收来自客户端的连接请求
	 *		  (将接受到的客户端请求放置到对应的队列中)
	 * 第二个参数	队列长度为10
	 */
	 if(listen(sockfd, 10) < 0){
	 	perror("liten error");
		exit(1);
	 }
	 /*
	  * 步骤4：调用accept函数从队列中获得一个客户端的请求
	  *	       连接,并返回新的socket描述符
	  * 注意：如果没有客户端连接，调用此函数会阻塞，
	  *		  直到获得一个客户端的连接。
	  */
	 struct sockaddr_in clientaddr;
	 socklen_t		clientaddr_len = sizeof(clientaddr);

	//设置线程的分离属性
	pthread_attr_t	attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,
					PTHREAD_CREATE_DETACHED);

	 while(1){
	 	//主控线程accept
	  	int fd = accept(sockfd, NULL, NULL);
		if(fd < 0){
			perror("accept error");
			continue;
		}
		/*
		 * 步骤5： 调用IO函数（read/write）和
		 *		   连接的客户端进行双向的通信
		 */
		pthread_t	th;
		int err;
		if((err = pthread_create(&th, &attr,
						th_fn, (void*)fd)) != 0){
			perror("pthread create error");
		}
		pthread_attr_destroy(&attr);
	}

	return 0;
}
