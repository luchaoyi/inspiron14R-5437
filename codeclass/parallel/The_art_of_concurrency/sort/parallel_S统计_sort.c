#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


/*数组排序，原数组不动使用统计排序，计算出顺序，可并行化每个循环统计一个数字位置
 *并行统计排序
 * */


#define ARRAY_SIZE 100000

int array[ARRAY_SIZE];
int sortedarray[ARRAY_SIZE];


void init(int *array){
	srand((unsigned) time(NULL)); //用时间做随机种子，每次产生随机数不一样
	int i;
	for (i=0;i<ARRAY_SIZE;i++){
		array[i]=rand()%1000;
		//printf("%d,",array[i]);
		sortedarray[i]=-1;
	}
	printf("\n");
}


int main(){
	init(array);

	int i;
	//int nCores=omp_get_num_procs();



/*
 *默认由核心数个线程执行for,静态调度则每个线程执行一部分for循环，均匀划分
 * */

/*
 *假设顺序排序，小->大，这里计算出>number的个数
 * */
#pragma omp parallel for 
	for(i=0;i<ARRAY_SIZE;i++){
		int lt=0; //统计>,<,=个数
		int eq=-1; //eq=eq-1,排除自身
		//int gt=0;
		int number=array[i];
		int j;
		for(j=0;j<ARRAY_SIZE;j++){
			if(array[j]==number)
				eq++;
			else if (array[j]<number)
			{
				lt++;
			}
		}

		
		if(sortedarray[lt]==-1)    //lt |=| gt
		{
			sortedarray[lt]=number;
			while(eq>0)  //多个number,除了number还有eq个number 
			{
				sortedarray[lt+eq]=number;
				eq--;
			}
		}
	}


	printf("-------\n");
	for(i=0;i<ARRAY_SIZE;i++){
		//printf("%d,",sortedarray[i]);
	}
	printf("\n");
	return 0;
}

/*
real	0m47.309s
user	2m16.784s
sys	0m0.116s

real	0m39.146s
user	2m20.232s
sys	0m0.208s

*/



