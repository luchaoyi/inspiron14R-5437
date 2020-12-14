/*
思想:	对于所有顶点调用DFS
记录DFS调用次数就是连通分量个数
*/
void GraphSearch(Graph G)
{
	int count=0;	
	for(i=0;i<G->v;i++) pre[i]=-1;
	
	for(i=0;i<G->V;i++)
		if(pre[i]==-1)
		{	
			count++;//记录DFS调用次数就是连通分量个数 count==1 则为连通图
			DFS(G,EDGE(i,i));	
		}
}
