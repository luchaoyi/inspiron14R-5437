#include<omp.h>
#include<stdio.h>
#include<stdlib.h>


#define ARRAY_SIZE 100

int array[ARRAY_SIZE]={0};


void init(int *array){
	int i;
	for (i=0;i<ARRAY_SIZE;i++){
		array[i]=i%10;
		printf("%d,",array[i]);
	}
	printf("\n");
}


int main(){
	init(array);

	int i;
	int nCores=omp_get_num_procs();

	int *count_3_array=(int *)calloc(nCores,sizeof(int));
	int count_3=0;




/*
 *默认由核心数个线程执行for,静态调度则每个线程执行一部分for循环，均匀划分
 * */

#pragma omp parallel for reduction(+:count_3)
	for(i=0;i<ARRAY_SIZE;i++){

		int id=omp_get_thread_num();
		if (array[i]==3){
			count_3_array[id]+=1;
		}


		if(array[i]==3){
			count_3+=1;
			printf("%d,threadId:%d\n",count_3,id);
		}

	}

	printf("%d\n",count_3);

	int sum=0;
	for(i=0;i<nCores;i++){
		printf("%d\n",count_3_array[i]);
		sum+=count_3_array[i];
	}

	printf("%d\n",sum);
	return 0;
}
