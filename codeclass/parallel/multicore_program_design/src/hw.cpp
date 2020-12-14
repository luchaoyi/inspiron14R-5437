#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<pthread.h>

//g++ hw.cpp -lpthread -o hw

#define THREAD_NUMBER 2

int retval_hello1=2;
int retval_hello2=3;

void *hello1(void *arg){
	char *hello_str=(char*)arg;
//	sleep(1);
	printf("%s\n",hello_str);

	pthread_exit(&retval_hello1); //线程退出
}

void *hello2(void *arg){
	char *hello_str=(char*)arg;
//	sleep(2);
	printf("%s\n",hello_str);

	pthread_exit(&retval_hello2); //线程退出
}

int main(int argc,char* argv[]){
	int i;
	int ret_val;
	int *retval_hello[2];

	//线程创建所需变量
	pthread_t pt[THREAD_NUMBER];
	const char* arg[THREAD_NUMBER];

	arg[0]="hello thread 1";
	arg[1]="hello thread 2";


	printf("Begin create threads ...\n");

	ret_val=pthread_create(&pt[0],NULL,hello1,(void *)arg[0]); //&pt[0] is pt ,thread 1 start exec hello1  
	if(ret_val!=0)
	{
		printf("thread create error!\n");
		exit(1);
	}

	ret_val=pthread_create(&pt[1],NULL,hello2,(void *)arg[1]); //&pt[0] is pt ,thread 2 start exec hello2  
	if(ret_val!=0)
	{
		printf("thread create error!\n");
		exit(1);
	}

	//当mian thread create sub thread(非detached状态) 
	//sub thread 结束后资源没有自动释放，而需要另一个线程调用pthread_join()释放资源
	//若sub thread处于detached状态则结束时自己释放资源，不需要pthread_join()，若执行 pthread_join则会报错
	//join会挂起线程等待指定线程结束
	
	printf("Now,the main thread returns!\n");
	printf("Begin to wait for threads...\n");
	
	for(i=0;i<THREAD_NUMBER;i++){
		ret_val=pthread_join(pt[i],(void**)&retval_hello[i]);
		if(ret_val!=0)
		{
			printf("pthread_join error!\n");
			exit(1);
		}
		else{
			printf("return value%d\n",*retval_hello[i]);
		}

	}

	return 0;
}
