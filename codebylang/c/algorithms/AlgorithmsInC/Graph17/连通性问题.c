#include<stdio.h>
#define N 1000


//用数组表示节点根下标为节点构造树
//同一个树为连通节点

main()
{
	int id[N];
	int p,q;
	
	for(i=0;i<N;i++) id[i]=i;
	
	while(scanf("%d %d\n",&p,&q)==2)
	{
		if(id[p]==id[q]) continue;
		
		
		for(t=id[p],i=0;i<N;i++)
		{
			if(id[i]==t) id[p]=id[q];//后来居上，全部变为id[q];
			//数据全部刷新
		}
	}
}
/************************************************************************/
//快速合并树型结构
for(i=p;i!=id[i];i=id[i]);
for(j=q;i!=id[j];j=id[j]);
//寻根
if(i==j) continue;
id[i]=j;//q根做根

//加权快速合并
int i,j,id[N];sz[N];

//初始化
//id=i
//sz[N]=1

for(i=p;i!=id[i];i=id[i]);
for(j=q;i!=id[j];j=id[j]);


//寻根
if(i==j) continue;
//核心思想：统计树的节点个数将 小树连接在大树上

if(sz[i]<sz[j]){id[i]=j;sz[j]+=sz[i];}
else{id[j]=i;sz[i]+=sz[j];}

/*******************************************************************/
//带有路径压缩的加权快速合并
//核心思想是：将访问对象p-q都挂在新树根节点压扁树
int i,j,id[N];sz[N];

//初始化
//id=i
//sz[N]=1

for(i=p;i!=id[i];i=id[i]);
for(j=q;i!=id[j];j=id[j]);


//寻根
if(i==j) continue;
//小树连接在大树上

if(sz[i]<sz[j])
{	id[i]=j;
	//q挂载
	sz[j]+=sz[i];
	//加权挂载
	
	//路径压缩
	id[p]=j;
	//p直接挂载载根上
	sz[j]+=sz[p];
	
}
else{
	id[j]=i;
	sz[i]+=sz[j];
	
	id[q]=i;
	sz[i]+=sz[q];
}
/*************************************************************/
//带有加权的等分路径压缩

//带有路径压缩的加权快速合并
//核心思想是：将访问对象p-q都挂在新树根节点压扁树
int i,j,id[N];sz[N];

//初始化
//id=i
//sz[N]=1

//等分核心思想：将节点的根更改为根的根
for(i=p;i!=id[i];i=id[i])
	id[i]=id[id[i]];
for(j=q;i!=id[j];j=id[j])
	id[j]=id[id[j]];
	

//寻根
if(i==j) continue;
//小树连接在大树上

if(sz[i]<sz[j])
{	id[i]=j;
	//q挂载
	sz[j]+=sz[i];
	//加权挂载
	
	//路径压缩
	id[p]=j;
	//p直接挂载载根上
	sz[j]+=sz[p];
	
}
else{
	id[j]=i;
	sz[i]+=sz[j];
	
	id[q]=i;
	sz[i]+=sz[q];
}























id[i]=j;//q根做根
