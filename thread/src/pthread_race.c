#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

//定义线程运行函数
void* th_fn(void *arg)
{
	int distance = (int)arg;
	int i;
	for(i = 1; i <= distance; i++)
	{
		printf("%lx run %d\n", pthread_self(), i);
		int time = (int)(drand48() * 100000);
		usleep(time);	//微秒
	}
//	return (void*)0;
	return (void*)distance;
}

int main(void)
{
	int err;
	pthread_t		rabbit, turtle;
	//创建rabbit线程
	if((err = pthread_create(&rabbit, NULL,
						th_fn, (void*)50)) != 0)
	{
		perror("pthread_create error");
	}

	if((err = pthread_create(&turtle, NULL,
						th_fn, (void*)50)) != 0)
	{
		perror("pthread_create error");
	}

	int result;
	//sleep(10);
	//主控线程调用pthread_join(),自己会阻塞
	//直到rabbit和turtle线程结束方可运行
	pthread_join(rabbit, (void*)&result);
	printf("rabbit race distance is %d\n", result);
	pthread_join(turtle, (void*)&result);
	printf("turtle race distance is %d\n", result);

	printf("control thread id: %lx\n", pthread_self());
	printf("finished\n");

	return 0;
}
