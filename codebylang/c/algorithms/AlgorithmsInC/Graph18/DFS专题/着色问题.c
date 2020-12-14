
/*
核心思想:
数组标记
正向递归时V----->t c->1-c->c->1-c 
逆向返回时是反的t-->v所以检测当前t是否等于v
即递归搜索时是着色返回时是检查

*/



/邻接表
struct node{int v; link next;}
typedef struct node *link;

struct graph
{
	int V;
	int E;
	link *adj;
	int* color;
} *Graph;


int DFScolor(Grapg G,int v,int c) 
{
	link t;
	//v--->i1--->i2...>w;
	G->color[v]=c
	
	
	for(t=G->adj[w];t!=NULL;t=t->next)
		if(G->cc[t->v]==-1)
		{
			DFScolor(G,t->v,1-c);
		}
		//v=c t=1-c才正常
		else if(G->color[t->v]!=1-c) return 0;
	return 1;
}

int Graphccolor(Graph G)
{
	int v,id=0;
	
	G->color=(int*)malloc(G->V*sizeof(int));
	
	for(i=0;i<G->V;i++) G->color[i]=-1;
	
	for(i=0;i<G->V;i++)
		if(G->color[i]==-1)
		{	
			
			if(DFScolor(G,i,0)) return 1; //可着色
			
		}
	return 0;	
}
