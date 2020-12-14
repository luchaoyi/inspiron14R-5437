#include<pthread.h>
#include<stdio.h>

pthread_cond_t cv;
pthread_mutex_t mutex;

int length;
int queue[200];




void *producer(void *param){
	for(int i=0;i<200;i++){
		pthread_mutex_lock(&mutex);
		queue[length++]=i;
		pthread_cond_signal(&cv);  //向等待条件队列的线程发送一个信号，唤醒一个线程

		pthread_mutex_unlock(&mutex);
	}
}

void *producer(void * param){
	item_t *item;
	for(int i=0;i<200;i++){
		pthread_mutex_lock(&mutex);
		queue[length++]=i;
		pthread_cond_broadcast(&cv); //向all wait 线程 send a signal,唤醒 all thread
		pthread_mutex_unlock(mutex);
	}
}



void *consumer(void *param){
	for(int i=0;i<200;i++){
		int seconds=0;
		pthread_mutex_lock(&mutex);
		while(length==0){
			pthread_cond_wait(&cv,&mutex); //处于等待时，会先释放现在持有的mutex,醒来时继续持有
		}

		int item = queue[--length];
		pthread_mutex_unlock(&mutex);
	}
}


int main(){
	pthread_t threads[2];
	pthread_cond_init(&cv,0);
	pthread_mutex_init(&mutex,0);
	length=0;

	pthread_create(&threads[0],0,producer,0);
	pthread_create(&threads[1],0,consumer,0);

	pthread_join(&threads[1],0);
	pthread_join(&threads[0],0);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cv);
}
