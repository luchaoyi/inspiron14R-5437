
#define  INFINITY 10000 //无穷大

int MinEdge(PshorEdge shortEdge,vertexNum)
{
    int temp=INFINITY ;
    int j=-1;
/*
	也是找边的过程
	生成树是找边
*/
}
void Prim(MGraph G)
{
	//最小生成树本质就是找出所有最短边将图所有点相连
	
    //初始化辅助数组
    //辅助数组存储最短边邻接点和权值
    //i个顶点需要i-1条边相连
    for(i=1;i<G.vertex;i++)
    {
        shortEdge[i].lowcost=G.arc[0][i];

        shortEdge[i].adjvex=0;//初始从V0开始
    }
    shorEdge[0].lowcast=0;//当前点加入集合即相对集合路径为0

    for(i=1;i<G.vertex;i++) //i个顶点需要i-1条边相连
    {
            k=MinEdge(shorEdge,vertexNum);//寻找最短
            shorEdge[k].lowcast=0;//当前点加入集合即相对集合路径为0

            //调整集合当前数组
            //由于集合加入新点以前为最短路径所以比较以下新点路径将更短的修正
            //集合扩大
           for(j=1;j<G.vertex;j++)
            if(G.arc[k][j]<shortEdge[j].lowcost)//新加入点到任意点距离
            {
                    shortEdge[j].lowcost=G.arc[k][j];
                    shortEdge[j].adjex=k;//集合中离此点最近的点 j->k临界 一条最短边
                    
            }
    }




}
