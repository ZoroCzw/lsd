#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
	char 	name[20];
	int 	time;
	int 	start;
	int 	end;
}RaceArg;

void*	th_fn(void *arg)
{
	RaceArg *r = (RaceArg*)arg;
	int i = r->start;
	for(; i <= r->end; i++)
	{
		printf("%s(%lx) running %d\n",
				r->name, pthread_self(), i);
		usleep(r->time);
	}

//	return (void*)0;	//pthread_exit((void*) 0);
	return (void*)(r->end - r->start);
}

int main(void)
{
	int err;
	pthread_t	rabbit, turtle;

	RaceArg r_a =
		{"rabbit", (int)(drand48()*100000000), 20, 50};
	RaceArg t_a =
		{"turtle", (int)(drand48()*100000000), 10, 60};

	if((err = pthread_create(&rabbit, NULL,
						th_fn, (void*)&r_a)) != 0)
	{
		perror("pthread_create error");
	}

	if((err = pthread_create(&turtle, NULL,
						th_fn, (void*)&t_a)) != 0)
	{
		perror("pthread_create error");
	}

	int result;
	pthread_join(rabbit, (void*)&result);
	printf("rabbit race distance %d\n", result);
	
	pthread_join(turtle, (void*)&result);
	printf("turtle race distance %d\n", result);
	printf("race finished\n");
//	pthread_join(rabbit, NULL);
//	pthread_join(turtle, NULL);

	printf("control thread id: %lx\n", pthread_self());
	printf("finished\n");
	
	return 0;
}
	
