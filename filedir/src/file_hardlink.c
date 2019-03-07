#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, 
			"usage: %s srcfile files \n", argv[0]);
		exit(1);
	}

	int i;
	for(i = 2; i < argc; i++)
	{
		if(link(argv[1], argv[i]) < 0)	//(源文件， 新文件)
		{
			perror("link error");
			continue;
		}
	}
	printf("creat success\n");
	return 0;
}
