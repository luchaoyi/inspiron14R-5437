/*
线程数设置原则
	1.每个线程运行循环次数不小于a(e.g. a=4)次，不能粒度太小
	2.总的运行线程数最大不超过b(e.g. b=2)倍CPU核数
	3.一般线程数=CPU核数性能较好，没有切换开销
*/
#include<omp.h>
const int g_nCore=omp_get_num_procs();
//n为总迭代次数
//min_n为线程最小迭代次数
int dtn2(int n,int min_n){
	int max_tn=n/min_n; //最大线程数
	int tn=max_tn>2*gnCore?2*gnCore:max_tn; //最大不超过2*gnCore 
	if(tn<1)
		tn=1;
	return tn;
}


/**
 *
 *usage:
#pragma omp parallel for num_threads(dtn2(n,MIN_ITERATOR_NUM))
	for{
	...
}
 *
 */
