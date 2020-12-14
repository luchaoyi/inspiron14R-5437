
typedef struct ArcNode
{
    int adj;

    struct ArcNode *next;

}ArcNode;
//链接节点

typedef struct
{
    DataType vertex;

    ArcNode *firstedge;

}vertexNode
//数组节点

typedef struct
{
    vertexNode adjlist[MSX_SIZE]
    int verNum,arcNum;
}ALGraph;


void InitGraph(ALGraph &G,DataType a[],int n,int e)
{
    G.verNum=n;
    G.arcNum=e;

//初始化数组
    for(i=0;i<G.verNum,i++)
    {
        G.adjlist[i].vertex=0;
        G.adjlist[i].firstedge=NULL;
    }
//
    for(k=0;k<G.arcNum;i++)
    {
        scanf(&i,&j);//输入边

        s=(ArcNode*)malloc(sizeof(ArcNode));

        s->adj=j;


        //采用头插法
        s->next=G.adjlist[i].firstedge;//插到表头
        G.adjlist[i].firstedge=s;
    }
}


void DFSTraverse(ALGraph &G,int v)
{
    printf(G.adj[v].data);
    visited[v]=1;


    p=G.adjlist.firstedge;
    //p为工作指针

   while(p!=NULL)
   {

       if(visited[p->adj]==0)//如果为访问过且有路径
        DFSTraverse(ALGraph,p->adj);
	
	//visited[p->adj]==1
        p=p->next;//递归回溯时p指向当前点的其它未访问的节点
   }
}

void BFSTraverse(ALGraph &G,int v)
{
    front = rear =-1;
    printf(G.adjlist[v].vertex);
    visited[v]=1;
    Q[++rear]=v;

    while(front!=rear)//队列非空
    {
        v=Q[++front];

        p=G.adjlist[v].firstedge;

        while(p!=NULL)
        {
            if(visited[p->adj]==0)//未访问过
            {

                //访问
                visited[p->adj]=1//标志
                Q[++rear]=p->adj;//入队
            }
            p=p->next;//广度在搜索
        }

    }

}
