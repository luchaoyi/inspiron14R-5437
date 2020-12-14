#include<stdlib.h>
#include <unistd.h>  //sleep 声明位置
#include<stdio.h>
#include<omp.h>


void demo_taskwait(){
#pragma omp task 
		{
			printf("task\n");
			sleep(3);
		}
#pragma omp task 
		{
			printf("task\n");
			sleep(3);
		}

//taskwait会等待task完成后执行
#pragma omp taskwait
		{
			printf("taskwait\n");
		}
}

int main(){



	omp_set_nested(1); //开启嵌套
#pragma omp parallel sections
	{
	printf("thread numbers %d\n",omp_get_num_threads());
#pragma omp section 
		{
			printf("s0 thread id %d\n",omp_get_thread_num());
#pragma omp parallel for
			for(int i=0;i<4;i++)
			{
				printf("section 0,i=%d,thread id %d\n",i,omp_get_thread_num());
			}
			printf("s0 thread id %d\n",omp_get_thread_num());
		
		}

#pragma omp section
		{
			printf("s1 thread id %d\n",omp_get_thread_num());
#pragma omp parallel for 
			for(int i=0;i<4;i++)
			{
				printf("section 1,i=%d,thread id %d\n",i,omp_get_thread_num());
			}
			printf("s1 thread id %d\n",omp_get_thread_num());
		}
	
	}
	
	
	demo_taskwait();	
	
	return 0;
}
