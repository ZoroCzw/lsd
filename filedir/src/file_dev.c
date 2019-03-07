#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
void out_dev(dev_t devno)
{
	//生成主设备号和次设备号
	int mj = major(devno);
	int mi = minor(devno);
	printf("(%5d, %5d)", mj, mi);
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "uasge: %s files \n", argv[0]);
		exit(1);
	}

	struct stat buff;
	int i;
	for(i = 1; i < argc; i++)
	{
		memset(&buff, 0, sizeof(buff));
		if(lstat(argv[i], &buff) < 0)
		{
			perror("lstat error");
			continue;
		}
		printf("%-20s", argv[i]);
		//判断是否是字符设备文件和块设备文件
		if(S_ISCHR(buff.st_mode) ||
			S_ISBLK(buff.st_mode))
		{
			printf("device file: ");
			//输出特殊设备号
			out_dev(buff.st_rdev);
		}
		printf("	on: ");
		//输出所有文件具有的设备号(包括主、次设备号)
		out_dev(buff.st_dev);
		printf("\n");
	}

	return 0;
}
