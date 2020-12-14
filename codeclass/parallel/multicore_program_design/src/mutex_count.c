#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define THREAD_NUMBER 10


//mutex使用前需要初始化
//使用pthread_mutex_init(...),函数初始化mutex,或直接使用静态赋值的方法
static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

int sum=0;

//线程执行体为回调函数，in/out参数类型均为void *
void *inc(void *arg){
	int i=(*(int *)arg);

	//加解锁
	pthread_mutex_lock(&mutex);
	sum+=i;
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(){
	pthread_t pt[THREAD_NUMBER];
	int i;
	int arg[THREAD_NUMBER];
	
	for(i=0;i<THREAD_NUMBER;i++){
		arg[i]=i;
		if( pthread_create(&pt[i],NULL,inc,(void *)&arg[i]) != 0){
			printf("pthread_create error\n");
			exit(1);
		}
	}

	for(i=0;i<THREAD_NUMBER;i++){
		if(pthread_join(pt[i],NULL) !=0)
		{
			printf("pthread_join error\n");
			exit(1);
		}
	}

	printf("sum is %d\n",sum);
	pthread_mutex_destroy(&mutex); //销毁锁,释放资源
}



