/*
在DFS搜索标记数组填入起始节点如果同一个起始则连通
用id标记次序
/相当于count记录DFS调用次数
//id记录访问次序在同一次序调用中访问过的节点连通
*/


//邻接表
struct node{int v; link next;}
typedef struct node *link;

struct graph
{
	int V;
	int E;
	link *adj;
	int*cc;
} *Graph;


void DFS(Grapg G,int w,int id) 
{
	link t;
	//v--->i1--->i2...>w;
	G->cc[w]=id//记录访问顺序
	
	
	for(t=G->adj[w];t!=NULL;t=t->next)
		if(G->cc[t->v]==-1)
		{
			DFS(G,t->v,id);
		}
}

int Graphcc(Graph G)
{
	int v,id=0;
	
	G->cc=(int*)malloc(G->V*sizeof(int));
	
	for(i=0;i<G->V;i++) G->cc[i]=-1;
	
	for(i=0;i<G->V;i++)
		if(G->cc[i]==-1)
		{	
			//相当于count记录DFS调用次数
			//id记录访问次序在同一次序调用中访问过的节点连通
			DFScc(G,i,id++);
		}	
}

int IsConnect(Graph G,int v,int w)
{	//id记录访问次序在同一次序调用中访问过的节点连通
	return G->cc[v]==G->cc[w];
}

