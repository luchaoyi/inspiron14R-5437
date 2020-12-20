
typedef struct ArcNode
{
    int adj;

    struct ArcNode *next;

}ArcNode;
//���ӽڵ�

typedef struct
{
    DataType vertex;

    ArcNode *firstedge;

}vertexNode
//����ڵ�

typedef struct
{
    vertexNode adjlist[MSX_SIZE]
    int verNum,arcNum;
}ALGraph;


void InitGraph(ALGraph &G,DataType a[],int n,int e)
{
    G.verNum=n;
    G.arcNum=e;

//��ʼ������
    for(i=0;i<G.verNum,i++)
    {
        G.adjlist[i].vertex=0;
        G.adjlist[i].firstedge=NULL;
    }
//
    for(k=0;k<G.arcNum;i++)
    {
        scanf(&i,&j);//�����

        s=(ArcNode*)malloc(sizeof(ArcNode));

        s->adj=j;


        //����ͷ�巨
        s->next=G.adjlist[i].firstedge;//�嵽��ͷ
        G.adjlist[i].firstedge=s;
    }
}


void DFSTraverse(ALGraph &G,int v)
{
    printf(G.adj[v].data);
    visited[v]=1;


    p=G.adjlist.firstedge;
    //pΪ����ָ��

   while(p!=NULL)
   {

       if(visited[p->adj]==0)//���Ϊ���ʹ�����·��
        DFSTraverse(ALGraph,p->adj);
	
	//visited[p->adj]==1
        p=p->next;//�ݹ����ʱpָ��ǰ�������δ���ʵĽڵ�
   }
}

void BFSTraverse(ALGraph &G,int v)
{
    front = rear =-1;
    printf(G.adjlist[v].vertex);
    visited[v]=1;
    Q[++rear]=v;

    while(front!=rear)//���зǿ�
    {
        v=Q[++front];

        p=G.adjlist[v].firstedge;

        while(p!=NULL)
        {
            if(visited[p->adj]==0)//δ���ʹ�
            {

                //����
                visited[p->adj]=1//��־
                Q[++rear]=p->adj;//���
            }
            p=p->next;//���������
        }

    }

}
