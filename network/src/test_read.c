#include "msg.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main( )
{
	char buff[512];
	read_msg(STDIN_FILENO, buff, sizeof(buff));
	printf("%s\n", buff);
	return 0;
}


