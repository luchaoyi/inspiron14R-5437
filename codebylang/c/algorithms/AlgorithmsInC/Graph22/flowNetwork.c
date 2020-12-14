/*************************************************************************
    > File Name: flowNetwork.c
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年01月17日 星期六 10时29分00秒
    > Update Time: 2015年01月17日 星期六 10时29分00秒
 ************************************************************************/

#include<stdio.h>


typedef node *link;

struct node
{
	int v;

	int cap;
	int flow;
	link dup;
	link next;
};

struct graph{
	int V;
	int E;

	link *adj;
};


link NEW(int v,int cap,int flow,link next)
{

	link x = malloc(sizeof *x);

	x->v=v;
	x->cap=cap;
	x->flow=flow;
	x->next=next;

	return x;
}

Graph GRAPHinit(int V)
{
	int i;
	Graph g = malloc(sizeof *g);
	g->adj = malloc(V* sizeof (link));

	g->V = V;
	G->E = 0;


	for( i =0;i<V;i++) g->adj[i] = NULL;

	return g;
}


void GraphInsertE(Graph G,Edge e)
{
	int v =e.v;int w=e.w;
	
	//巧妙实现了头插法 --> 新节点 -->老节点
	//
	//流入流出正负表示 只需统计所有E e.flow   计算流入出量之差 中间节点若无储存则 ==0 
	//
	G->adj[v] = NEW(w,e.cap,e.flow,G->adj[v]);
	G->adj[w] = new(v,-e.cap,-e.flow,G->adj[w]);

	G->adj[v]->dup = G.adj[w];
	G->adj[w]->dup = G.adj[v];

	G->E++;
}

static int flowV(Graph G,int v)
{
	link t;
	int x =0;

	for (t=G->adj[v];t!=NULL; t =t->next)
	{
		x+=t->flow;

	}
	return x;
}

int GrpahFlowCheck(Graph G,int s,int t)
{
	int v,int val=flowV(G,s);
	for (v=0;v<G->V;v++)
	{
		//中间节点为0 
		if((v!=s) &&(v!=t))
			if(flow(G,v)!= 0 ) return 0;

	}

	if(val+flowV(G.t)!=0) return 0;//--> == <-- 

	if (val <0 ) return 0 // --> <0
}



static int wt[maxWT]; //相当于L（vi）
//Ford - Fulkerson
//

//计算调整量 正向 u->flow   反向 cap-flow
#define Q(u->cap<0 ? -u->flow:u->cap-u->flow)
#define P(Q>wt[v]> wt[v]:Q)

//v-u 所以可可能调整量为 min（Q，wt[v]）

int Graphpfs(Graph G,int s,int t,link st[])
{
	int v,int w,d=M;
	link u;
	

	PQinit();
	priority = wt;

	for (v=0;v<G->V;v++)
	{
		st[v] = NULL,wt[v] = 0 ;PQinsert(v);
	}

	wt[s] = M;
	PQinc(s);

	while(!PQempty())
	{
		v=PQdelmax();


		//v-->u 
		if(vt[v] == 0 || v==t) break;

		//从某点开始 访问它的所有邻接点
		for(u=G->adj[v];u!=NULL;u=u->next)
		{
			if(Q>0)
			{

				if(P > wt[w = u->v])
				{
					wt[w] = P ;//v->w 边的调整量
					PQinc(w) ;
					st[w] =u;

				}

			}

		}

		wt[v] = M;

		if (wt[t] == 0) return 0;

		//反向追踪
		for (w=t;w!=s;w=st[w]->dup->v)
		{
			u=st[w];d=(Q > d? d:Q);

		}

		return d;
	}

}

void GRAPHmaxflow(Graph G,int s,int t)
{
	int x,intd;
	link st[maxV];

	while((d=Graphpfs(G,s,t,st)!=0))
	{
		for(x=t;x！=s;x=st[x]->dup->v)
		{
			st[x] -> flow +=d; //后向
			st[x] ->dup->flow -=d; //前向
		}
	}
}
