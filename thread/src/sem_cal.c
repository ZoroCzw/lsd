#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

typedef struct
{
	int 	sum;
	sem_t 	sem;
}Result;

void* set_fn(void *arg)
{
	Result *s = (Result*)arg; 
	int i = 1;
	for( ;i <= 100; i++)
	{
		s->sum+=i;
	}

	sem_post(&s->sem);

	return (void*)0;
}

void* get_fn(void *arg)
{
	Result *s = (Result*)arg;
	
	sem_wait(&s->sem);

	printf("0x%lx result %d\n", pthread_self(), s->sum);

	return (void*)0;
}

int main(void)
{
	int err;
	pthread_t set, get;
	Result	r;
	r.sum = 0;

	sem_init(&r.sem, 0, 0);

	if((err = pthread_create(&set, NULL,
				set_fn, (void*)&r)) != 0){
		perror("pthread create error");			
	}

	if((err = pthread_create(&get, NULL,
				get_fn, (void*)&r)) != 0){
		perror("pthread create error");			
	}

	pthread_join(set, NULL);
	pthread_join(get, NULL);

	sem_destroy(&r.sem);

	return 0;
}




