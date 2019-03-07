#include "job.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


Job* creat_job(char *cmd)
{
	Job *job = (Job*)malloc(sizeof(Job));
	assert(job != NULL);
	job->cmd =
		(char*)malloc(sizeof(char) * strlen(cmd));
		assert(job->cmd != NULL);
		strcpy(job->cmd, cmd);
		job->progs_num = 0;
		job->progs = NULL;
		return job;
}

void destroy_job(Job *job)
{
	assert(job != NULL);
	free(job->progs);
	free(job->cmd);
	free(job);
}

static int arg_num(char **arg)
{
	int i = 0;
	char *start = arg[0];
	while(start != NULL)
	{
		i++;
		start = arg[i];
	}
	return i;
}

Program* creat_program(char **arg)
{
	Program *prog =
		(Program*)malloc(sizeof(Program));
	assert(prog != NULL);
	int counter = arg_num(arg);
	prog->args = 
		(char**)calloc(counter+1, sizeof(char*));
	int i;
	for(i = 0; i < counter; i++)
	{
		int len = strlen(arg[i]);
		prog->args[i] = (char*)malloc(len);
		assert(prog->args[i] != NULL);
		strcpy(prog->args[i], arg[i]);
	}
	prog->args[i] = NULL;
	return prog;
}

void destroy_program(Program *prog)
{

}

int add_program(Job *job, Program *prog)
{

}

