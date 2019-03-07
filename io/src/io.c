#include "io.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_LEN 4096

void copy(int fdin,int fdout)
{
	char buffer[BUFFER_LEN];
	ssize_t size;
//	lseek(fdin, 0L, SEEK_END);
	while( (size = read(fdin, buffer, BUFFER_LEN)) > 0)
	{
		
		if(write(fdout, buffer, size) != size)
		{
			fprintf(stderr, "write error: %s\n",
				strerror(errno));
		exit(1);
		}
	}
	if(size < 0)
	{
		fprintf(stderr, "read error: %s\n",
			strerror(errno));
		exit(1);
	}
}

void set_fl(int fd, int flag)
{
	//获得原来的文件状态标志
	/*	int fcntl(int fd, int cmd, ...)
	*	返回：成功依赖于cmd，出错返回-1
	*	（1）复制已有描述符
	*	（2）获取/设置文件描述符标志cmd=F_GETFD或F_SETFD
	*	（3）获取/设置文件状态标志
	*	（4）获取/设置文件异步I/O权
	*	（5）获取/设置记录锁
	*/
	int val = fcntl(fd, F_GETFLi, 0);	//返回对应文件描述符标志
	//增加新的文件状态标志
	val |= flag;
	if(fcntl(fd, F_SETFL, val) < 0)
	{
		perror("fcntl error");
	}
}

void clr_fl(int fd, int flag)
{
	int val = fcntl(fd, F_GETFL, 0);
	val &= ~flag;
	if(fcntl(fd, F_SETFL, val) < 0)
	{
		perror("fcntl error");
	}
}

int lock_reg(int fd, int cmd, short type, 
	off_t offset, short whence, off_t length)
{
	struct flock flock;
	flock.l_type = type;
	flock.l_start = offset;
	flock.l_whence = whence;
	flock.l_len = length;
	//flock.l_pid = getpid();
	//l_pis:加锁、解锁进程的进程号（pid）
	if(fcntl(fd, cmd, &flock) < 0)
	{
		perror("fcntl error");
		return 0;
	}
	return 1;
}

