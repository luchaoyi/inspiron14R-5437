/*************************************************************************
    > File Name: bellman.c
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年01月16日 星期五 14时55分27秒
    > Update Time: 2015年01月16日 星期五 14时55分27秒
 ************************************************************************/

#include<stdio.h>




void GRAPHbf(Graph G,int s,int st[],double wt[])
{
	int v,w;link t; int N=0;
	QUENEinit(G->E);  
	for (v=0;v<G->V;v++)
	{
		st[v] = -1;
		wt[v] = maxWT;
	}
	wt[s] = 0;st[s]=0; //start s

	QUENEput(s);
	QUENEput(G->V); //G->V是观察哨


	while(!QUENEempty())
	{
		
		if(v = QUENEget() == G->V)
		{
			if(N++ >G->V)
				return 
			QUENEput(G->V)

		}
	//得到一个点 开始点 检查此点所有连接边
	//对其判断此点连接的边的点的最短距离是否可以经过此点
	//的边的更小 连接边更新
	//将这些点进入队列
	//从这些点除法寻找
	//考量直到所有点 都进入过 也是考察过所有 点是否能被搭桥
		else
			//链上 所有点
			for(t = G->adj[v];t!=NULL;t=t->next)
			{
				if(wt[w = t->v] > wt[v] + t->wt)
				{
					wt[w] = wt[v] + t->wt;
					QUENEput(w);
					st[w] = v;
				}
			}
	}


}
