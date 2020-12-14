
/*
	简单路径搜索
*/
//大局观
//搜索v->w路径
//如果v==w找到了
//如果没找到继续找
//如果到最后还没找到就是失败
int pathR(Graph G,int v,int w,int* visited)
{
	//v--->w;
	visited[w]=1;
	//到达此地就输出printf(v->w);
	if(v==w) return 1;
	
	for(i=0;i<G->V;i++)]
		if (G->adj[w][i]==1 && visited[i]==0)
			//v----->i .......>w
			if(pathR(G,i,w,visited)) //找到后停止搜索返回
				return 1;
	
	return 0;	
} 

int path_search(Graph G,int v,int w)
{
   for(i=0;i<G->V;i++) visited[i]=0;
   pathR(G,v,w,visited);//路径搜索中...
}


/*
	哈密顿路径
*/
//改变路径搜索算法
//1找到路径长度为V才停止
//2若深度搜索失败则将visited数组更改为0在搜
int pathR(Graph G,int v,int w,int* visited,int d)
{
	//v->w;
	visited[w]=1;
	//到达此地就输出printf(v->w);
	if(v==w) return 1;
	
	for(i=0;i<G->V;i++)]
		if (G->adj[w][i]==1 && visited[i]==0)
			if(pathR(G,i,w,visited,d-1)) //找到后停止搜索返回
				return 1;
	
	visited[v]=0;
	return 0;	
} 

int Search(Graph G,int v,int w)
{
   for(i=0;i<G->V;i++) visited[i]=0;
   pathR(G,v,w,visited,G->V-1);//路径搜索中...
}

/*
	欧拉路径的存在性
	性质：连通图中路径所有度为偶数
	v--->w
	或全为偶数：欧拉回路
	两个顶点的度为奇数：欧拉路径
	路径一进一出为偶数
	
*/

int GraphathE(Graph G,int v,int w)
{
	int t;
	
	//GRAPHdeg得到两个顶点的度
	t=GRAPHdeg(G,v)+GRAPHdeg(G,w);//顶点要么为两个奇数或全图为偶数
	
	if(t%2!=0) return 0;
	
	for(i=0;i<G->V;i++)
		if((i!=v) && (i!=w))
		{
			if(GRAPHdeg(G,i)%2!=0) return 0;
		}
	
	return 1;
	
}

/*
	欧拉路径的搜索
	为保证每条路径走一遍所以每走过一条边则删除此边
	边表实现
	遍历路径删除走过的边
	
	//邻接矩阵版更改一下简单路径搜索就行
*/
int path(G,v)
{
	int w;

	for(;G->adj[v]!=NULL;v=G->adj[v]->v)
	{
		Stackpush(v);
		w=G->adj[v]->v;
		
		GraphRemove(G,v,w);
	}
	//此时搜索到底了没有下一条路了返回此点
	return v;
	
}
//这里使用了栈将经过的点压入了栈中
void pathshow(Graph G,int v,int w)
{
	v->w;
	printf(w);//栈逆序
	
	v--------path---->w;
	//if(v==w)
	//则为欧拉回路
	while(path(G,v)==w && !Stackempty())
	{
		v=Stackpop();
		printf(v);
	}
}



