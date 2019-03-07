#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		printf("usage: %s scrfile destfile\n", argv[0]);
		exit(1);
	}

	int sfd = open(argv[1], O_RDONLY);
	if(sfd < 0)
	{
		perror("open error");
		exit(1);
	}
	int dfd = open(argv[2],
				O_RDWR | O_CREAT | O_TRUNC, 0777);
	if(dfd < 0)
	{
		perror("open error");
		exit(1);
	}

	long len = lseek(sfd, 0, SEEK_END);
	printf("len: %ld\n", len);
	lseek(dfd, len-1, SEEK_SET);
	write(dfd, "0", 1);
	/*	void *mmap(void *addr, size_t len, int prot, int fd, off_t off);
	*		返回值：成功返回映射区起始地址;出错返回MAP_FAILED
	*		addr通常取0，表示系统选择该映射区起始地址
	*		fd 要映射文件的文件描述符
	*		prot映射区的保护要求 PROT_READ PROT_WRITE PROT_EXEC PROT_NONE
	*		flag MAP_SHARED：描述了本进程对映射区所进行的存储操作的配置
	*		off通常指定为0
	*/
	char *a1 = mmap(0, len, PROT_READ,				//映射区可读
					MAP_SHARED, sfd, 0);
	if(a1 < 0)
	{
		perror("mmap error");
		exit(1);
	}
	char *a2 = mmap(0, len, PROT_WRITE,
					MAP_SHARED, dfd, 0);
	if(a2 < 0)
	{
		perror("mmap error");
		exit(1);
	}
	memcpy(a2, a1, len);
	munmap(a1, 0);
	munmap(a2, 0);

	close(sfd);
	close(dfd);

	return 0;
}
