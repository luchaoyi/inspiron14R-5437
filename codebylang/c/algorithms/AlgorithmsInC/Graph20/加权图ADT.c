typedef struct {int v ;int w;double wt;} Edge;
Edge EDGE(int ,int double); 


struct
{
	int V;//number of vertex
	int E;//number of edge
	
	double **adj;//weight matrix
}

Graph GRAPHinit(int V)
{
 int v;
 Graph G= malloc(sizeof(Graph));
 
 G->adj=MATRIXdouble(V,V,MAXWT);
 
}

void GRAPHinsertE(Graph G,Edge e)
{
	if(G->adj[e.v][e.w]==MAXWT) G->E++;
	G->adj[e.v][e.w]=e.wt;
	G->adj[e.w][e.v]=e.wt;
}

//...
