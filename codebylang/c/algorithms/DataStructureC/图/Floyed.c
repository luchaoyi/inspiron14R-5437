
void Floyed(MGraph G)
{
    int Distance[MAXV][MAXV];
    int path[MAXV][MAXV];

    int i,j,k;

    for(k=0;k<G.vertexNum;k++)
        for(i=0;i<G.vertexNum;i++)
            for(j=0;j<G.vertexNum;j++)
                if(Distance[i][j]>Distance[i][k]+Distance[k][j])
                {
                    Distance[i][j]=Distance[i][k]+Distance[k][j];//修改路径长度
                    path[i][j]=k;//i->j通过k搭桥
                }
}

//递归搜索
void print(int path[][MAXV],int i,int j)
{
    if(path[i][j]!=j)
    {
        printf(i->path[i][j]->j);
        print(path,i,path[i][j]);//
    }
}
