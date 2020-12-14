#include<pthread.h>


//gcc demo_helgrind.c -lpthread    link pthread
//valgrind --tool=helgrind ./a.out 检测数据争用
int counter=0;


void * func(void *params){
	counter++;
}

int main(){
	pthread_t thread1,thread2;

	pthread_create(&thread1,0,func,0);
	pthread_create(&thread2,0,func,0);
	pthread_join(thread1,0);
	pthread_join(thread2,0);
	return 0;
}
