#include<stdio.h>
#include<omp.h>


int next_task=0;

int get_next_task(){
	int task;
#pragma omp critical
	{
		if(next_task<MAX_TASK){
			task=next_task;
			next_task++;
		}else
		{
			task--;
		}
	}

	return task;
}

void task_queue(){
	int my_task;
#pragma omp parallel private(my_task)
	{
		my_task=get_next_task();
		while(my_task!=-1){
			//get_task_done(my_task)
			my_task=get_next_task();
		}
	}
}

//根据线程号分配任务
void demo(){
	int myid;
#pragma omp parallel private(myid)
	{
		myid=omp_get_thread_num();
		if(myid==0)
			//...
	}


//使用工作分区可以做到不同线程执行不同任务
#pragma omp parallel sections
	{
#pragma omp section 
		//

#pragma omp section 
		//
	}
}










