
//kruskal算法对边操作
//采用边集数组存储
#define MAX_V  M //最多点数
#define MAX_E  N //最多边数


//存储边数组结构
struct EdgeType
{
    int from,to,weight;

};

typedef struct
{
    DataType vertex[MAX_V];
    EdgeType  edge[MAX_E];
    int vertexNum,edgeNum;//顶点数，边数
}EdgeGraph;

/// ///对边集数组处理前安权排序，可加快速度
//parent数组表示点的双亲节点

int Findroot(int parent[],int v)
    {

        if(parent[v]>-1)//说明已有父节点
            return parent[v];
        else
            return v;
    }

void Kruskal(EdgeGraph G)
{
    for(i=0;i<G.vertexNum;i++)
        parent[i]=-1;//初始化
    for(num=0,i=0;i<G.edgeNum;i++)
    {
        vertex1=Findroot(parent,G.edge[i].from);
        vertex2=Findroot(parent,G.edge[i].to); //寻找最小边父节点

        if(vertex1!=vertex2)//位于不同根树则可以连接
            //if== 则同父节点若相连则出现环
        {
            //连接此边
            //保存边或打印边

            parent[vertex2]=vertex1;
            num++;
            if(num==n-1) break; //n的顶点相连至少需要 n-1条边

        }


    }

}


