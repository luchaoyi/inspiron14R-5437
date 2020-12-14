
//邻接矩阵

int pre[V];//标记访问次序
//BFS不考虑图不连通情况
//可以调用循环BFS搜索非连通图
//初始从一点开始e.v=e.w;
void BFS(Graph G,Edge e)
{
	int v,w;
	int cnt=0;
	
	
	v=e.v;
	st[v]=v;
	pre[v]=cnt++;
	QUEUEput(v);//queue
	
		
	while(!QUEUEempty())
	{	
		
		v=QUEUEout();
		
		for(w=0;w<G->V;w++)
			if(1==G->adj[v][w])
			{
				if(-1==pre[w])
					{	//v->w;
						st[w]=v;//w节点的父节点是v
						pre[w]=cnt++;//访问入队列
						QUEUEput(w);
						
					}
					
					
			}
		
	}						
}
