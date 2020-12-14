/*
 *奇偶排序，两两交换，不大范围比较交换，交错奇偶，直到没有交换发生
 *偶:<0 1> <2,3> <4,5> 两两交换互相不干涉，因此可并行循环
 *奇:<1,2> <3,4> <5,6>
 奇偶排序每个线程负载比较均匀，可伸缩性强
*/

#include<omp.h>
#include<stdio.h>
#include "comm.h"




/*
real	1m42.369s
user	6m40.620s
sys	0m0.296s

*/

void Odd_Even_sort0(int *array,int N){


	int i;
	int start=0; //start=0 偶,start=1奇数
	int flag=1;   //交换标志

	int temp;

	while(start || flag){ //start在条件中，保证完成一次奇交换和一次偶交换,以确保第一个和最后一个被处理到
		flag=0;
#pragma omp parallel for private(temp)
		for(i=start;i<N-1;i+=2)
		{
			if(array[i]>array[i+1])
			{
				exch(&array[i],&array[i+1]);
				flag=1;     //flag的竞争是良性竞争，即线程对它修改的是同一个值
			}
		}
		start=start?0:1;  
	}
}





void Odd_Even_sort1(int *array,int N){

printf("start\n");


	int i;
	int start=0; //start=0 偶,start=1奇数
	int flag;

 /*提升并发层次 
  *移到循环之外，避免线程频繁创建
  * */

#pragma omp parallel 
	{

#pragma omp single
		{
		flag=omp_get_num_threads();  
		printf("%d\n",flag);
		}


	while(1){ 
		if(flag < 0 && start == 0) break;

		

#pragma omp critical 
		{
			flag--;    //注意flag不在是良性的,若一个线程执行flag=0则其它线程读取会结束while 
			//flag不论赋值为多少长期不执行交换则最终会递减<0
			//printf("%d\n",flag);
		}

#pragma omp barrier 

#pragma omp for 
		for(i=start;i<N-1;i+=2)
		{
			if(array[i]>array[i+1])
			{
				exch(&array[i],&array[i+1]);
#pragma omp critical 				
				flag=omp_get_num_threads(); //flag++;是错误的，一次没交换不代表下次没交换，要保证所有线程始终运行   
	
			}
		}

#pragma omp single
		{
		start=(start?0:1);  
		}
	}
}

}


/*
real	2m1.557s
user	7m12.804s
sys	0m0.964s


real	1m40.143s
user	6m34.196s
sys	0m0.276s

*/

//改进，奇数和偶数放在不同的并行区域内
void Odd_Even_sort2(int *array,int N){


	int i;
	int trips=0; 
	int exch0,exch1=1;   //交换标志

	while(exch1){ 
		exch0=0;
		exch1=0;

#pragma omp parallel 
		{	
#pragma omp for 
		for(i=0;i<N-1;i+=2)
		{
			if(array[i]>array[i+1])
			{
				exch(&array[i],&array[i+1]);
				exch0=1;     
			}
		}

		//初始trips=0,至少保证一次奇交换
		if(exch0||!trips){
#pragma omp for 
		for(i=1;i<N-1;i+=2)
		{
			if(array[i]>array[i+1])
			{
				exch(&array[i],&array[i+1]);
				exch1=1;     
			}
		}

	}//if
	}//parallel
		trips=1; //trips只用一次，只是为了保证至少一次奇数一次偶数
}
}



int main()
{
	int i;
	init(array);
	Odd_Even_sort2(array,ARRAY_SIZE);

	for(i=0;i<ARRAY_SIZE-1;i++)
		//printf("%d,",array[i]);

	return 0;
}
