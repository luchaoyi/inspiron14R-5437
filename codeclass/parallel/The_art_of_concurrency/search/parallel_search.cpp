#include<omp.h>


/*
 *并行分区域搜索时，对于没有重复元素的数组,在某个线程已搜索到时通知其它线程结束搜索
 * */
int Parallel_Search(void **ppData,int nLen,void *pData,COMPAREFUNC comp){
	int i,k;
	int nRet=-1;
	int nCores=omp_get_num_procs(); //核数

	int nStep=nLen/nCores; //按核数划分搜索区域，每一个核运行一个线程，搜索一个区域
#pragma omp parallel for
	for(k=0;k<nCores;k++) //在每一个k下，并行块内部区域并行
	{
		int begin=k*nStep;
		int end=(k+1)*nStep;
		if(k==nCores-1)
		{
			//e,g, 10/3==3  mod==1, |3 |3 |4 ,最后一个核要处理所有
			end=nLen;
		}
		//这个for在并行块内部，且没有声明为并行，因此是每一个并行线程内串行
		for(i=begin;i<end;i++)
		{
			if((*comp)(ppData[i],pData)==0)
			{
				//注意这里nRet是没有保护的共享变量，若不同线程有重复的pData,都会对nRet赋值
				//此时nRet最终是最后一个被修改的值
				nRet=i;
			}
		}
	}
	return nRet;
}

//搜索最大数字
int Parallel_Search_Max(void **ppData,int nLen,COMPAREFUNC comp){
{

	int i,k;
	int nCores=omp_get_num_procs(); //核数 
	int *pnMax=(int *)malloc(nCores*sizeof(int)); //每个parallel thread最大index存储到此数组，最终比较.
	if (pnMax==NULL)
	{
		return -1;
	}
	int nStep=nLen/nCores; //按核数划分搜索区域，每一个核运行一个线程，搜索一个区域
#pragma omp parallel for
	for(k=0;k<nCores;k++) //在每一个k下，并行块内部区域并行
	{
		int begin=k*nStep;
		int end=(k+1)*nStep;
		if(k==nCores-1)
		{
			end=nLen;
		}

		int nMax=begin;
		for(i=begin+1;i<end;i++)
		{
			if((*comp)(ppData[i],ppData[nMax])>0)
			{
				nMax=i;
			}
		}
		pnMax[k]=nMax;
	}

	int nMax=pnMax[0];
	for(i=1;i<nCores;i++)
	{
		if((*comp)(ppData[pnMax[i]],ppData[nMax])>0){
			nMax=pnMax[i];
		}
	}
	free(pnMax);
	return nMax;
}

//终止检测
//改进，若已经有线程搜索到目标，则其它线程应该退出
//要广播消息让其它进程知道
//使用开销最小的原子操作,立flag,检测是否终止
//标志判断会增加开销，但可以让程序提前退出
//折中，可以减少判断标志次数，一次比较多个数据后判断一次flag
