#define INFINITY INT_MAX 
#define MAX_VERTEX_NUM 20

//图的存储1 邻接矩阵
typedef enum{DG,DN,UDG,UDN
} GrapgKind; //有向图\网，无向图\网


typedef struct ArcCell
{
	VRType adj; //连接关系or权值

	InfoType *info; //弧附加信息
}

typedef struct{
	VertexType vex[MAX_VERTEX_NUM]; //顶点信息
	AdjMatrix arcs; //邻接矩阵

	int vexnum,arcnum;
	GraphKind kind;
}MGraph;


//图的存弧2 邻接表和逆邻接表


//图的存弧3 十字链表

... InsertArc(G,(v,w,...))
{
	t=(Arc*)malloc(sizeof(Arc));
	if(...) exit...;

	t->headvex=v;t->tailvex=w;
	t...;


	//v --> out -->hlink
	if(!(p=G[v].firstin))
	{
		G.firstin=t;
	}
	else
	{
		while(p->hlink)
		{
			p=p->hlink; //同以v为弧头 v->*
		}
		p->hlink=t;
	}


	//这是尾插入法插入到十字链表中
	//同理得
	//w --> in -->tlink  w<-*
	if(!(p=G[w].firstout))
	{
		G.firstout=t;
	}
	else
	{
		while(p->tlink)
		{
			p=p->tlink; //同以v为弧头 v->*
		}
		p->tlink=t;
	}
	//同样可以采用头插法更简单
	
	{
		...
	}
}



...DFSTraverse(...)
{	for ... visit[i]=FALSE; //访问过?

	for(...)
	{
		if(!visit[v]) DFS(G,v);
	}
}

...DFS(G,v)
{
	Visit(v);
	visit[v]=0;

	for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w))
		if(!...) DFS(w);
}



void MiniSpanTree_PRIM(MGraph,VertexType u)
{
	struct {
		VertexType adjvex;
		VRType lowcost;
	}closedge[MAX_VERTEX_NUM];

	k=Locate(G,u);

	//init 
	for(i=0;i<G.vexnum;i++)
	{
		//all vex near u cost is u-vex
		closedge[i]=(u,G.arcs[k][j].adj); //初始集合只有u集合外点到u最近，最近距离为各点到u距离
	}

	closedge[k].lowcost=0;

	//生成树n个顶点需n-1条边
	for(i=1;i<G.vexnum;i++)
	{
		k=minmum(closedge); //select min 


		
		output(G[k].adjvex,G.vex[k]) //output此边 

		closedge[k].lowcost=0;

		//不断扩大集合范围选择离集合最近节点加入集合
		//更新到集合的距离即查看新点加入造成的最近集合距离更改
		//更该集合外的点到集合最短距离时应记录下具体是离到集合哪个点距离更近


		//update
		for(j=0;j<G.vexnum;j++)
		{
			//k新点，查看k到各点集合
			//集合-->各点距离
			if(G.arcs[k][j].adj < closedge[j].lowcost)
			{
				closedge[j]={G.vex[k],G.arcs[k][j]};
			}
		}
	}


}


DFS(G,v)
{
	visit[v]=++count;

	for(...)
		//v的下一个点（v->w）w没有访问则访问
		//若已经访问了则,会遇到更小的 
		if(visit[w]==0)
			DFS(...)
		else 

}



//拓扑排序
//AOE网,节点时间表示入射活动结束，出射活动开始，节点时间发生遵循拓扑序。前面活动未完则后面活动无法开始
Status TopologicalSort(ALGraph G,Stack &T){
	FindInDegree(G,indegree);
	InitStack(S);
	InitStack(T);
	ve[0...G.vexnum-1] = 0; //节点最早发生时间,关键路径，最长路径

	for(i=0;i<G.vexnum;i++)
		if(!indegree[i]) Push(S,i); //利用栈保存要检查点，不重复检验已查过的点
	count=0;//对输出节点计数,如果AOV网有环则存在点入度永远不为0则拓扑输出的点少于G.vexnum

	while(!isStackEmpty(S))
	{
		Pop(S,i);
		Push(T,i); //保存到T逆拓扑排序顺序	
		printf(i,G.vex[i].data) ;count++;


		for(...){

			k=p->adjvex;
			if(--indegree[k]==0) Push(S,k);

			//i最早发生的时间
			if(ve[i]+*(p->info) > ve[k])  ve[k]=ve[j]+*(p->info);
		}
	}
	if(count<G.vexnum) return ERROR; 
	else return OK;
}


//结束节点为汇点最早发生时间即为最长路径也是最迟发生时间，因为后面没有时间了
Status CriticalPath(ALGraph G,Stack &T,int &C)
{
	if(!TopologicalSort(G,T)) return ERROR;
	vl[...]=ve[...];

	while(!StackEmpty(T))
	{
		for(Pop(T,j),p=G.vex[j].firstarc;p;p=p->nextarc)
		{
			k=p->adjvex; //j-->k
			dut=*(p->info);
			if(vl[k]-dut<vl[j]) vl[j]=vl[k]-dut;

		}
	}

	for(j=0;j<G.vexnum;j++)
	{
		for(p=G.vex[j].firstarc;p;p=p->nextarc)
		{
			k=p->adjvex;dut=*(p->info);

			ee=ve[j];
			el=vl[k]-dut;

			tag=(ee==el)? '*' :'';
			printf(j,k,dut,ee,el,tag);
		}
	}
	
}

//           s出发点
...Dijstra(G,s)
{
	//D[i] s->i最短路径长度
	//C[i] if s->i最短路径为 s->j->i 则C[i]=j if s->i C[i]=j;
	for(i=0;i<G->vexnum;j++) //init
	{
		//s-->i s-->s==0  s!-->** == INF
		D[i]=G.w[s][i];
		C[i]=i;
	}

	for(i=1;i<G.vexnum;i++) //最多需要n-1次
	{
		//select min 
		min=INF;
		mindex=-1;

		for(i=0;i<G->vexnum;i++)
		{
			if(D[i]>min)
			{
				min=D[i];
				mindex=i;
			}	
		}

		//
		for(...)
		{
			if(D[i]>D[mindex]+G.w[mindex][i])
			{
				D[i]=D[mindex]+G.w[mindex];
				C[i]=mindex;
			}
		}
		D[mindex] = INF; 

	}
	
}
//start s Dijstra 计算的是从某个源点出发到其它各点的距离 
GetPath(C,end)
{

	i=end;

	//表示有路径
	while(C[i]=!i)
	{
		push(S,i);
		i=C[i];
	}
	//s->i -- ...end
	
	path[0]='s';path[1]=i;

	i=2
	while(...)
	{
		
		path[i++]=pop(S);
	}
}
