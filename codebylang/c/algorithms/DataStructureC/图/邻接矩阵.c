typedef struct
{
    DataType vertex[MAX_SIZE];//
    short arc[MAX_SIZE][MAX_SIZE];//

    int vertexNum,int arcNum;
}MGraph;



//深度遍历
//前序遍历
//递归或栈实现
void DFSTraverse(MGraph &G,int v)//v 遍历开始点编号
{
    printf(G.vertex[v]);
    visited[v]=1;//标志已经访问


    for(i=0;i<G.vertexNum;i++)
        if(G.arc[v][i]==1 && visited[v]==0)
        {
            DFSTraverse(G,i);
        }
}

//广度遍历
//层序遍历
//队列实现
void BFSTraverse(MGraph &G,int v)
{
    rear=front=-1;
    printf(G.vertex[v]);
    visited[v]=1;//标志

    Q[++rear]=v;
    while(rear!=front) //队列非空
    {
         v=Q[++front];
        for(i=0;i<G.vertexNum;i++)
            {
                 if(G.arcNum[v][i]==1&&visited==0)
                 {
                     printf(G.vertex[i];
                     visited[i]=1;
                     Q[++rear]==i;
                 }
            }
    }
}
