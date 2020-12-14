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

inline void exch(int *a,int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
