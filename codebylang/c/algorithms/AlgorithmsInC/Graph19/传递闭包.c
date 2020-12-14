/*
	计算传递关系
	矩阵相*简单粗暴
	
	warshall算法：关系传递
	
	若S-->i  i-->t 则 s--t
	
	性质：任何传递闭包算法都可以计算bool阵相乘
	
*/
 
 for(i=0;i<v;i++)//桥
 	for(s)
 		if(A[s][i]==1)//判断提出来优化效率提高
 		for(t)
 			if(A[i][t]==1)
 				A[s][t]=1;
 				
 
 
 
/*改造的warshall算法类似folyed*/
	for
		for
			for ;s->i;i->t;
				if(2==A[s][i]+[A[i][t])
					A[s][t]=1;

/*DFS搜索所有可达节点集计算*/
/*基于深度搜索的闭包计算*/

void search(G,e)
{
		G->A[e.v][e.w]=1;
		
		for(t=G->adj[e.w];t!=NULL;t=t->next)
			if(G->A[e.v][t->v]==0)//若搜索可达则矩阵置1,若为1则已经搜索过
				search(G,EDGE(e.v,t->v)); //若深度搜索中v起始-->v1---->v2--->v3---则G->A[v][v1]=1;若搜索可达则矩阵置1
	
}


void DFS(G)
{
	for(v=0;v<V;v++)
		{
			search(G,EDGE(v,v));//对所有深度搜索到达点置1
		}
}













