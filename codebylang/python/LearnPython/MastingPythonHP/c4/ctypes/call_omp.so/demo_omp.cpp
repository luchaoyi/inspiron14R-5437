#include<stdio.h>
#include<omp.h>



//g++ -shared -o demo_omp.so -fPIC demo_omp.cpp -fopenmp
//g++ -shared -o no_demo_omp.so -fPIC demo_omp.cpp 

//编译C++动态库时，需要加上__cplusplus
#ifdef __cplusplus
       extern "C" {
          void sp();
		  void demo0();
		  void demo1();
		  void demo2();
		  void demo3();
		  void demo4();
	   }
#endif


void sp()
{
	printf("---\n");
}

void demo0()
{
	sp();
#pragma omp parallel
	{
		printf("hello,world!\n");
		printf("threads num %d\n",omp_get_num_threads());
	}
	
	sp();
#pragma omp parallel num_threads(8)
	{
		printf("hello,world!,ThreadId=%d\n",omp_get_thread_num());
		printf("threads num %d\n",omp_get_num_threads());
	}


	printf("cpu procs %d\n",omp_get_num_procs());


	int i=15;
#pragma omp parallel for
	for(i=0;i<5;i++)
	{
		printf("%d\n",i);
	}
	sp();
	printf("%d\n",i);
	
	
	
	
/*
 *parallel if sub stmt,if cond satisfy
 * */

#pragma omp parallel if(i>10) num_threads(2)
	{
		//满足i>10则设置两个线程
		printf("A hello,world!\n");
#pragma omp single 
		{
			//single中的语句只执行一次，且执行时其它线程处于阻塞状态
		printf("single!\n");
		}
		printf("B hello,world!\n");
	}

	//sum原本是共享变量需要加锁保护，reduction后将创建sun私有版本拷贝，离开时对每个私有版本sum进行+运算,赋值给共享sum
	int sum=100;
#pragma omp parallel for reduction(+:sum)
	for(i=0;i<10;i++)
	{
		sum+=i;
		printf("sum:%d\n",sum);
	}
		printf("sum:%d\n",sum);
}


int counter=10;
#pragma omp threadprivate(counter)   

int increment_counter(){
	counter++;
	return counter;
}


void demo1(){

#pragma omp parallel
	{
		int count;
#pragma omp single copyprivate(counter)
/*copyprivate用一个私有变量将某个值广播到其它线程*/
		{
			counter=50;
		}
		count=increment_counter();
		printf("ThreadId:%d,count=%d\n",omp_get_thread_num(),count);
	}



/*
 *parallel sections 定义一个并行区块，不同区是串行的。
  sections的section对区分段，不同section并行执行
 * */
#pragma omp parallel sections copyin(counter)
	/*
	 * copyin会将counter值拷贝到各个线程
	 */
	{
#pragma omp section
		{
			printf("%d\n",counter+1);
		}
#pragma omp section 
		{
			printf("%d\n",counter+2);
		}
#pragma omp section 
		{
			printf("%d\n",counter+3);
		}
	}

}




/*critical 设置一个临界区域，同一时间只有一个thread可以执行它
 * */
void demo2()
{
	int i,nVar=0;
#pragma omp parallel for shared(nVar)
	for(i=0;i<10;i++)
	{
#pragma omp critical
		{
			/*临界区对共享变量保护，等同于
				omp_set_lock(&lk);
				nVar+=1;
				printf("ThreadId %d,nVar %d\n",omp_get_thread_num(),nVar);
				omp_unset_lock(&lk);
			 * */
			nVar+=1;
			printf("ThreadId %d,nVar %d\n",omp_get_thread_num(),nVar);
		}

#pragma omp atomic
			nVar+=1; /*atomic 只能放置一条执行基本运算表达式，被翻译为原子操作*/
	}

}



/*ordered子句配合ordered命令使用，使指定块按循环迭代顺序执行,一个循环只能有一个ordered命令
 * */
void demo3()
{
#pragma omp parallel for ordered  
	for (int i=0;i<10;i++)
	{
#pragma omp ordered 
		printf("ThreadId %d,i %d\n",omp_get_thread_num(),i);
	}
}

/*omp某些命令隐含barrier，如
 * for 不同for块，串行执行
 * sections不同sections串行执行
 * nowait子句可以消除隐含的barrier
 * */





/*锁操作API
 * */


void demo4(){
	int i,nVar=0;
	omp_lock_t lk; /*omp_lock_t 锁类型变量*/
	omp_init_lock(&lk); /*init lock*/

#pragma omp parallel for shared(nVar)
		for(i=0;i<10;i++)
		{
				omp_set_lock(&lk);
				nVar+=1;
				printf("ThreadId %d,nVar %d\n",omp_get_thread_num(),nVar);
				omp_unset_lock(&lk);
		}

	omp_destroy_lock(&lk);
}


/*
int  main(int argc,char* argv[]){
	demo0();
	div();
	demo1();
	div();
	demo2();
	div();
	demo3();
	div();
	demo4();
	return 0;

}
*/

      
