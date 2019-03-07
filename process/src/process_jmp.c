#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h>

#define TOK_ADD 	5
#define TOK_SUB 	6

jmp_buf env;

void do_line(char *line);
void cmd_add(void);
void cmd_sub(void);
int  get_token(char *item);
char *prompt = "cal: ";

int main(void)
{
	ssize_t size = strlen(prompt) * sizeof(char);
	char buff[256];
	ssize_t len;

	//设置跳转点
	if(setjmp(env) < 0)
	{
		perror("setjmp error");
		exit(1);
	}
	
	write(STDOUT_FILENO, prompt, size);
	while(1)
	{
		len = read(STDIN_FILENO, buff, 256);
		if(len < 0)
		{
			break;
		}
		buff[len - 1] = 0;
		do_line(buff);
		write(STDOUT_FILENO, prompt, size);
	}

}

void do_line(char *line)
{
	int cmd = get_token(line);
	switch(cmd)
	{
		case TOK_ADD:
			cmd_add();
			break;
		case TOK_SUB:
			cmd_sub();
			break;
		default:
			fprintf(stderr, "error command\n");
	}
}

void cmd_add()
{
	int i = get_token(NULL);
	int j = get_token(NULL);
	printf("result is %d\n", i + j);
}

void cmd_sub()
{

	int i = get_token(NULL);
	int j = get_token(NULL);
	printf("result is %d\n", i - j);
}
static int is_number(char *item)
{
	int len = strlen(item);
	int i;
	for(i = 0; i< len; i++)
	{
		if(item[i] > '9' || item[i] < '0')
			return 0;
	}
	return 1;
}
/*
 * add 3 4
 * sub 5 7
 */
int get_token(char *line)
{
	char *item = strtok(line, " ");
	if(line != NULL)
	{
		if(!strcmp("add", item)) return TOK_ADD;
		if(!strcmp("sub", item)) return TOK_SUB;
	}
	else if(is_number(item))
	{
		int i = atoi(item);
		return i;
	}
	else
	{
		fprintf(stderr, "arg not number\n");
		//进行非局部跳转,1为返回值，作为setjmp的返回值
		longjmp(env, 1);
	}

}
