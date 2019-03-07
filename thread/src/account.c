#include "account.h"
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

//创建账户
Account* create_account(int code, double balance)
{
	Account *a = (Account*)malloc(sizeof(Account));
	assert(a != NULL);
	a->code = code;
	a->balance = balance;
	//对互斥锁进行初始化
	//pthread_mutex_init(&a->mutex, NULL);

	//对读写锁进行初始化
	//pthread_rwlock_init(&a->rwlock, NULL);
	
	//初始化线程信号量，0代表不在进程间共享，初始值设为1
	sem_init(&a->sem, 0, 1);
	return a;
}
//销毁帐号
void destroy_account(Account *a)
{
	assert(a != NULL);
	//销毁互斥锁
	//pthread_mutex_destroy(&a->mutex);

	//销毁读写锁
	//pthread_rwlock_destroy(&a->rwlock);

	//销毁信号量
	sem_destroy(&a->sem);

	free(a);
}
//取款
double withdraw(Account *a, double amt)
{
	assert(a != NULL);
	//对共享资源加锁
	//pthread_mutex_lock(&a->mutex);

	//上写锁
	//pthread_rwlock_wrlock(&a->rwlock);

	//信号量减1
	sem_wait(&a->sem);
	if(amt < 0 || amt > a->balance){
		//释放互斥锁
		//pthread_mutex_unlock(&a->mutex);

		//释放写锁
		//pthread_rwlock_unlock(&a->rwlock);

		//信号量加1
		sem_post(&a->sem);
		return 0.0;
	}
	double balance = a->balance;
	sleep(1);
	balance -= amt;
	a->balance = balance;
	//释放互斥锁
	//pthread_mutex_unlock(&a->mutex);
	
	//释放写锁
	//pthread_rwlock_unlock(&a->rwlock);

	//信号量加1
	sem_post(&a->sem);

	return amt;
}
//存款
double deposit(Account *a, double amt)
{
	assert(a != NULL);

	//pthread_mutex_lock(&a->mutex);

	//pthread_rwlock_wrlock(&a->rwlock);
	
	sem_wait(&a->sem);
	if(amt < 0){
		//pthread_mutex_unlock(&a->mutex);
		//pthread_rwlock_unlock(&a->rwlock);
		sem_post(&a->sem);
		return 0.0;
	}
	double balance = a->balance;
	sleep(1);
	balance += amt;
	a->balance = balance;
	
	//pthread_mutex_unlock(&a->mutex);
	//pthread_rwlock_unlock(&a->rwlock);
	sem_post(&a->sem);
	return amt;
}
//查看账户余额
double get_balance(Account *a)
{
	assert(a != NULL);
	
	//pthread_rwlock_rdlock(&a->rwlock);
	//pthread_mutex_lock(&a->mutex);
	sem_wait(&a->sem);
	sleep(1);
	double balance = a->balance;
	
	//pthread_mutex_unlock(&a->mutex);
	//pthread_rwlock_unlock(&a->rwlock);
	sem_post(&a->sem);

	return balance;
}


