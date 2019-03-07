#ifndef __MSG_H__
#define __MSG_H__
#include <stdio.h>
typedef struct{
	//协议头部
	char head[10];
	char checknum;//校验码
	
	//协议体部
	char buff[512];//数据

}Msg;
/*
 * 发送一个基于自定义协议的message
 * 发送的数据存在buff中
 */
extern int write_msg(int sockfd,
				char *buff, size_t len);

/*
 * 读取自定义协议的message
 * 读取的数据放在buff中
 */
extern int read_msg(int sockfd, 
				char *buff, size_t len);



#endif
