#include<semaphore.h>

sem_t semaphore;
sem_t limit;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int queue[10];
int queueLength;

void *producer(void *param){
	for(int i=0;i<500;i++){
		//申请空位,没有则阻塞 
		sem_wait(&limit);
//maybe producer and consumer will parallel exec so must use mutex 
		pthread_mutex_lock(&mutex);
		queue[queueLength++]=i;
		pthread_mutex_unlock(&mutex);
		sem_post(&semaphore);
	}
}

void *consumer(void * param){
	for(int i=0;i<500;i++){
		int item;
		if(queueLength==0) {sem_wait(&semaphore)};

		pthread_mutex_lock(&mutex);
		item=queue[--queueLength];
		pthread_mutex_unlock(&mutex);

		sem_post(&limit);
	}
}




int main(){
	pthread_t threads[2];
	sem_init(&semaphore,0,0);  //first 0 is show semaphore is thread shared,second 0 is means semaphore value init 0
	sem_init(&limit,0,10);

	pthread_create(&threads[0],0,producer,0);
	pthread_create(&threads[1],0,consumer,0);

	pthread_join(&threads[0],0);
	pthread_join(&threads[1],0);

	sem_destroy(&limit);
	sem_destroy(&semaphore);

	return 0;
}
