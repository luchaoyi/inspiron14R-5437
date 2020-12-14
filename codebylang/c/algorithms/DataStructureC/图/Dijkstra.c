

int Min(/////)
{
    temp =INIF;
    j;
    for()
    {
        if(temp>dist[i]&&dist!=0)
        {
            temp=dist[i];
            j=i;
        }
    }
    return j;
}
//v为起始点可以找出v->其它各点的最短路径
void Dijkstra(MGraph G,int v)
{
    for(i=0;i<G.verNum;i++)
    {
        dist=G.arc[v][i];
        //
        if(dist[i]!=INIF)//无穷大可到达
        ///path保存dist对应 v ->i的路径
            path[i]="v->i";
        else
            path[i]=" ";
    }
    
    //path[i]保存从v出发到每个点的最短路径 

    for(num=1;num<G.vertexNum;num++)
    {
        k=Min(dist);//从数组中找到最小

        printf(path[k]);
        
        //扫描一遍dist数组
        for(i=0;i<G.vertexNum;i++)
        {
            if(dist[i]>dist[k]+G.arc[k][i])//如果直接到达>与间接到达间接到达说明是科学的
            {
                //贪心策略步步最优
                //当前步最优则通过不在回溯

                dist[i]=dist[k]+G.arc[k][i];

                path[i]="v->k->i"
            }
        }
        dist[k]=0;//将此最短路径加入集合
        /// 此处置零在Min（）函数中跳过disk[i]=0;
        ///if(temp>dist[i]&&dist!=0)
    }

}
