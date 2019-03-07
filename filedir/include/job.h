#ifndef __JOB_H__
#define __JOB_H__

typedef struct
{
	char **args;	//对应于主函数中的char *argv[]参数
}Program;

typedef struct
{
	char		*cmd;
	int			progs_num;
	Program		*progs;
}Job;

extern Job* creat_job(char *cmd);
extern void destroy_job(Job *job);
extern Program* creat_program(char **arg);
extern void destroy_program(Program *prog);
extern int add_program(Job *job, Program *prog);

#endif
