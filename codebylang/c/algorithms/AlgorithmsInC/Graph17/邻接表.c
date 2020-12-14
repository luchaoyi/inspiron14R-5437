
struct node{int v; link next;}
typedef struct node *link;

struct graph{int V;int E;link *adj;} *Graph;

link NEW(int v,link next)
{
	link temp=(link)malloc(sizeof(node));	
	temp->v=v;
	temp->next=next;
	
	return temp;
}

Graph GraphInit(int V)
{
	//
	//for
	G->adj[v]=NULL;
	return G;	
}
void GraphInsertE(Graph G,Edge e)
{
	
	int v=e.v,w=e.w;
	
	//使用头插法使插入时间为O(1);
	G->adj[v]=NEW(v,G->adj[v]);
	//w
	
	G->E++;	
}


