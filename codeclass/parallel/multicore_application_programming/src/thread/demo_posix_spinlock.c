#include<pthread.h>

pthread_spinlock_t lock;

void lockandunlock(){
	int i=10000;
	while(i>0){
		pthread_spin_lock(&lock);
		i--;
		pthread_spin_unlock(&lock);
	}
}


void lockandunlock_(){
	//使用trylock失败时立即返回
	int i=0;
	int count=0;

	while(i==0){
		if(pthread_spin_trylock(&lock)) //successful get
		{
			i++;
			pthread_spin_unlock();
		}
		else
			count++;
	}
	//记录的失败次数
	printf("Failed tries=%i\n",count);
}

int main(){
	pthread_spin_init(&lock,PTHREAD_PROCESS_PRIVATE); //进程私有,if PTHREAD_PROCESS_SHARED则进程共享
	lockandunlock();
	pthread_spin_destory(&lock);
}
