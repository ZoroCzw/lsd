#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int x, y;
	if(read(STDIN_FILENO, &x, sizeof(int)) < 0){
		perror("read error");
		exit(1);
	}

	if(read(STDIN_FILENO, &y, sizeof(int)) < 0){
		perror("read error");
		exit(1);
	}
	
	int result = x + y;

	if(write(STDOUT_FILENO, &result, 
				sizeof(int)) != sizeof(int)){
		perror("write error");
	}

	return 0;
}
