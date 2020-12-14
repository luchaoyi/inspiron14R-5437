#include<stdio.h>
#include "UF.h"

static int *id,*sz;

void UFinit(int N)
{
	id=(int*)malloc(N*sizeof(int));//保存根节点表示连通关系
	sz=(int*)malloc(N*sizeof(int));//树节点数量
	
	//id[i]=i;
	//sz[i]=1;
	
}

static int findroot(int x)  //static 私有函数不外接
{
	i=x;
	while(i!=id[i])
	{
		i=id[i];
	}
	return i;
}

int UFfind(int p,int q)
{
	return (find(p)==find(q));
}

void UFunion(int p,int q)
{
	int i=find(p);
	int j=find(q);
	
	
	if(sz[i]<sz[j]) 
	{
		id[i]=j;
		sz[j]+=sz[i]
	}
	else
	{
		id[j]=i;
		sz[i]+=sz[j];
	}

}
































