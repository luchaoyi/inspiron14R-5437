#include<stdlib.h>

struct	graph
{
	int V;//顶点数
	int E;//边数
	
	int** adj;//邻接矩阵地址
	int* dv;//顶点度数组
}graph,*Graph;

int ** MATRIXinit(int r,int c,int val)
{
	int **t;
	
	t=(int**)malloc(r*sizeof(int*));
	
	for(i=0;i<r;i++)
	{
		t[i]=(int*)malloc(c*sizeof(int));
	}
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
			t[i][j]=val;
	return t;
	
}

int * DVinit(int V)
{
	int *t;
	
	t=(int*)calloc(V*sizeof(int));	
	return t;
}

Graph GraphInit(int V)
{
	Graph G =(Graph)malloc(sizeof(graph));
	
	G->V=V;
	G->E=0;
	G->adj=MATRIXinit(V,V,0);
	G->dv=DVinit(V);
	return G;
}

void GraphInsertE(Graph G,Edge e)
{
	//e.v--e.w;
	int v=e.v;
	int w=e.w;
	
	if(0==G->adj[v][w])
		G->E++;
	G->adj[v][w]=1;
	G->adj[w][v]=1;//无向图
	//度增加
	G->dv[v]++;
	G->dv[w]++;
	
}

void GraphRemoveE(Graph G,Edge e)
{
	//e.v--e.w;
	int v=e.v;
	int w=e.w;
	
	if(1==G->adj[v][w])
		G->E--;
	G->adj[v][w]=0;
	G->adj[w][v]=0;//无向图
	G->dv[v]--;
	G->dv[w]--;
}

int GraphEdges(Edge e[],Graph G)//抽取边表
{
	//遍历矩阵将a[i][j]==1;的存入
	
	int v,w,E=0
	for(v=0;v<G->V;v++)
		for(w=v+1;w<G->V;w++)
		{
			if(1==G->adj[v][w])
				e[E]->v=v;
				e[E++]->w=w;
		}
	return E;	   
}

void GraphShow(Graph G)
{
	
	int i,j;
	for(i=0;i<G->V;i++)
	{
		//i:
		for(j=0;j<G->V;j++)
		{
			if(1==G->adj[i][j])
			{
				// j
			}
		}
		//:\n
	}
}

void Graphdeg(Graph G,int v)
{
	return G->dv[v];
}












