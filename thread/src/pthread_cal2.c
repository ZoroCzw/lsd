#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * 一个线程负责计算结果，多个线程负责获取结果
 */

typedef struct
{
	int				res;
	int				counter;	//统计获取结果的线程数量
	pthread_cond_t	cond;		//条件变量
	pthread_mutex_t	mutex;		//互斥锁
}Result;

//计算并将结果放置Result中的线程运行函数
void*	set_fn(void *arg)
{
	int i = 1, sum = 0;
	for(; i<=100; i++){
		sum += i;
	}
	Result *r = (Result*)arg;
	//将计算结果放到Result当中
	r->res = sum;

	pthread_mutex_lock(&r->mutex);
	//判断获取结果的线程是否到达等待数量
	while(r->counter < 2){
	//while(!r->is_wait){
		pthread_mutex_unlock(&r->mutex);
		usleep(100);
		pthread_mutex_lock(&r->mutex);
	}
	pthread_mutex_unlock(&r->mutex);
	
	//通知唤醒等待结果的线程
	pthread_cond_broadcast(&r->cond);
	
	return (void*)0;
}

//定义获取结果的线程运行函数
void*	get_fn(void *arg)
{
	Result *r = (Result*)arg;
	//对俩个线程共享的判断条件进行保护（加锁）
	//俩个线程对判断条件的操作是互斥的
	pthread_mutex_lock(&r->mutex);
	//代表获取结果的线程准备好了
	r->counter++;
	
	//获取结果的线程进行等待
	pthread_cond_wait(&r->cond, &r->mutex);
	//唤醒后
	pthread_mutex_unlock(&r->mutex);
	//获取计算结果
	int res = r->res;
	printf("0x%lx get sum is %d\n",
				pthread_self(), res);


	return (void*)0;
}

int main(void)
{
	int err;
	pthread_t	cal, get1, get2;
	Result r;
	r.counter = 0;
	pthread_cond_init(&r.cond, NULL);
	pthread_mutex_init(&r.mutex, NULL);

	if((err = pthread_create(&get1, NULL,
			get_fn, (void*)&r)) != 0){
		perror("pthread create error");
	}
	
	if((err = pthread_create(&get2, NULL,
			get_fn, (void*)&r)) != 0){
		perror("pthread create error");
	}

	if((err = pthread_create(&cal, NULL,
			set_fn, (void*)&r)) != 0){
		perror("pthread create error");
	}
	
	

	pthread_join(cal, NULL);
	pthread_join(get1, NULL);
	pthread_join(get2, NULL);

	pthread_cond_destroy(&r.cond);
	pthread_mutex_destroy(&r.mutex);

	return 0;
}

