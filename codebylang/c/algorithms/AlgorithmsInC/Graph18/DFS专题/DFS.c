//DFS:visit[N]数组标记是否访问过某节点
//一路向下试探直到底回朔
//也可以将visited中的置一是否标记改为访问顺序记录

//	st[e->w]=e->v; //标记父节点 v-->w可以构造一个DFS树

cnt=0 //标记数组和计数器 cnt==0 
int pre[G->V];//pre[i]=-1;

//初始边从 0-0 开始
void DFS(Grapg G,Edge e) 
{
	//v--->i1--->i2...>w;
	w=e.w;
	
	st[e->w]=e->v; //标记父节点 v-->w可以构造一个DFS树
	
	pre[w]=cnt++;//记录访问顺序
	
	for(i=0;i<G->V;i++)
	if(G->adj[w][i]==0)
		if(pre[i]==-1)
		{
			DFS(G,EDGE(w,i));
		}
}

//邻接表
struct node{int v; link next;}
typedef struct node *link;

struct graph{int V;int E;link *adj;} *Graph;

cnt=0 //标记数组和计数器 cnt==0 
int pre[G->V];//pre[i]=-1;

void DFS(Grapg G,Edge e) 
{
	link t;
	//v--->i1--->i2...>w;
	w=e.w;
	pre[w]=cnt++;//记录访问顺序
	
	
	for(t=G->adj[w];t!=NULL;t=t->next)
		if(pre[t->v]==-1)
		{
			DFS(G,EDGE(w,t->v));
		}
}



