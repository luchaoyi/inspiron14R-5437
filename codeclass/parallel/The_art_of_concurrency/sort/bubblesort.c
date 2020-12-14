/*
	像波浪冲刷海岸，多个线程并行执行，一浪与一浪不重叠则不会引发数据竞争
	一个线程先启动，然后设置安全点，过了安全点则启动后面线程，避免后面追上前面则不能越过安全点

	冒泡排序，将数据分区，每个区都作为一个临界区，如果前面线程不离开此区则后面线程不能进入
	设置缓冲地带
	
	冒泡并行由于锁竞争因此可伸缩性差，在更多核更多线程并发，可能出现空闲线程
*/

#include<omp.h>
#include<stdio.h>
#include "comm.h"


/*1000个数据一段一个锁*/
#define SEGNUMBER ((ARRAY_SIZE-1)/1000)

int main()
{


	init(array);
	int nCores = omp_get_num_procs();

	int Len=ARRAY_SIZE/SEGNUMBER;
	int i;

	omp_lock_t *lk=(omp_lock_t *)malloc(sizeof(omp_lock_t)*SEGNUMBER); //每一个段一个锁

	for(i=0;i<SEGNUMBER;i++){
		omp_init_lock(&lk[i]);
	}

	int k=0;
	int end=ARRAY_SIZE-1;


while(end>0)
{
#pragma omp parallel for num_threads(nCores) firstprivate(k)
	for(i=0;i<nCores;i++){
		int Done=0;
		int j=0;
		int release_point=0;
		int temp=0;


		while(!Done){
		//波浪式前进
		//波浪一波又一波
		omp_set_lock(&lk[k]);  // == lk+k 竞争第k个，执行完后释放竞争第k+1个数据一段一个锁

		//printf("thread %d,malloc lock %d\n",omp_get_thread_num(),k);


		if(k>=SEGNUMBER){
			release_point=ARRAY_SIZE-1;
		}else
		{
			release_point=(k+1)*Len;
		}

		while(j<release_point){
			if(array[j]>array[j+1])
			{
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
			}
			j++;
		}

		omp_unset_lock(&lk[k]);
		k++;

		if(j>=end)
		{
			Done=1;
			end--;
			k=0;
		}
		}

	}
}

	printf("*************\n");

	for(i=0;i<ARRAY_SIZE-1;i++)
		//printf("%d,",array[i]);

	return 0;
}


/*
real	0m50.343s
user	3m16.072s
sys	0m0.240s

real	0m24.414s
user	1m36.100s
sys	0m0.076s


*/

