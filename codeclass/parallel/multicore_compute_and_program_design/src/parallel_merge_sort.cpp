//并行归并排序，将数据划分为若干相等小区间并行排序，然后串行归并
//将区间划分为2^k个小区间则归并一次成2^(k-1)个小区间，k轮归并完成

#include<omp.h>
#define MAX_MERGE_TURN 24

void Parallel_MergeSort(void **ppData,int nLen,COMPAREFUNC func){
	int i,k;
	int nStep;

	int nLoopCount;
	int nCore;
	int nStart1,nEnd1;
	if (nLen<MIN_PARALLEL_SORT_COUNT){
		//数量太少，一个线程就可以,串行排序
		Serial_MergeSort(ppData,0,nLen-1.func);
		return ;
	}

	nCores=omp_get_num_procs();

	int nCount=nLen/MIN_PARALLEL_SORT_COUNT;

	int nTurn=MAX_MERGE_TURN;
	nLoopCount=1<<nTurn;//1<<nTurn==2**nTurn
	
	//找出合适的nLoopCount
	//即区间大小为MIN_PARALLEL_SORT_COUNT 共有nCount个区间，2**nTurn>=nCount
	//求最小nTurn
	while(nLoopCount>nCount)
	{
		nLoopCount=nLoopCount>>1;
		-- nTurn;
	}
	
	if((nLoopCount>nCore)&&(nTurn>0x1)&&((nTurn & 0x1)==1))
	{
		--nTurn;
		nLoopCount=nLoopCount>>1;
	}

	nStep=nLen/nLoopCount;
	int *p=new int[nLoopCount*2+CACHE_SIZE_LINE];
	int *pnPos=(int*)GetCacheAlignedAddr(p);

	//对nLoopCount个小区间并行排序
#pragma omp parallel for private(nStart1,nEnd1) num_threads(nCores)
	for (i=0;i<nLoopCount;i++){
		nStart1=i*nStep;
		nEnd1=nStart1+nStep-1;

		if(i==nLoopCount-1){
			nEnd1=nLen-1;
		}
		Serial_MergeSort(ppData,nStart1,nEnd1,func);
		//pnPos[2*i]
		//pnPos[2*i+1]
		pnPos[i+i]=nStart1;
		pnPos[i+i+1]=nEnd1;
	}
	//Merge
	
	//串行归并k次,每次区间较少一半
	for (k=0;k<nTurn;i++){
		//两两合并，互不干扰可以并行
		//nLoopCount-1个区间
		//
#pragma omp parallel for num_threads(nCores)
		for(i=0;i<nLoopCount-1,i+=2)
		{
			//Serial_Merge();

		}
		//合并一次
		nLoopCount=nLoopCount>>2;//区间少一半
	}

	//
	//return 
}


/*
 *数据划分，任务划分的方法是多种多样的
 * */

//负载均衡的并行基数排序
//从低位开始
//基数排序需要进行n轮,每位一轮
//并行排序对数据分段,没一个线程构造自己的箱子，并针对的部分数据分配到箱子
//分配完成后则将箱子连接形成全局箱子，开始下一轮


//分区排序
//从高位开始
//先分段并行分配后，将箱子连接在一起
//箱子1中的数据肯定小于箱子2数据
//因此，再以箱子分配数据,将每个箱子交给不同线程排序
//此事将所有箱子连接，自然有序
