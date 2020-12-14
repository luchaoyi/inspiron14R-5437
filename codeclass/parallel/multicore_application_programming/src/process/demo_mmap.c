//通过共享内存(like windows内存映射),IPC
//进程间共享互斥量

#include<sys/mman.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>

//gcc demo_mmap.c -lpthread -lrt
//未定义引用是没有包含link库，编译时要加对应-l*,具体函数可以man
 
int main(){


	//create a shared attr 
	pthread_mutexattr_t attributes;
	pthread_mutexattr_init(&attributes);
	pthread_mutexattr_setpshared(&attributes,PTHREAD_PROCESS_SHARED);

	int handle = shm_open("/shm",O_CREAT|O_RDWR,0777);
	ftruncate(handle,1024*sizeof(int));//set segment size  

	//连接到内存
	char *mem=(char *)mmap(0,1024*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,handle,0);

	//pthread 数据类型都以_t end 
	pthread_mutex_t *mutex;
	mutex=(pthread_mutex_t *)mem;
	pthread_mutex_init(mutex,&attributes);

	pthread_mutexattr_destroy(&attributes);

	//mem最开始存储了一个共享mutex
	int ret =0;
	int *pcount=(int *)(mem+sizeof(pthread_mutex_t));
	*pcount=0;

	pid_t pid = fork();
	if(pid==0){
		//sub process
		pthread_mutex_lock(mutex);
		(*pcount)++;
		pthread_mutex_unlock(mutex);
		ret=57;
	}else{
		int status;
		waitpid(pid,&status,0);
		printf("Child returned %i\n",WEXITSTATUS(status));
		pthread_mutex_lock(mutex);
		(*pcount)++;
		pthread_mutex_unlock(mutex);
		printf("Count=%i\n",*pcount);
		pthread_mutex_destroy(mutex);
	}

	munmap(mem,1024*sizeof(int));
	shm_unlink("/shm");
	return ret;
}
