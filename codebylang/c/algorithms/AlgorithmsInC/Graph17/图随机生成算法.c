
//17.7生成E条边稀疏图生成常用
int randV(Graph G)
{
	return G->V*rand()/(RAND_MAX-1);
}

Graph GraphRand(int V,int E) //生成顶点数--->边数
{
	Graph G=GraphInit(V);
	
	while(G->E<E)
	{
		GraphInsert(G,Edge(randV(G),randV(G)));//将随机生成的两个顶点连接成边并插入进图中
	}
	return G;
	
}

//17.8稠密图生成加入概率P
Graph GRAPHrand(int V,int E)
{
	int i,j;
	
	double p=(2.0*E/V)/(V-1);	//稠密度2e/v
	
	//
	
	for(i=0;i<G->V;i++)
		for(j=0;j<i;j++)
		{
			if(rand()<p*RAND_MAX)
				//插入边
		}
		
		return G;
		
}		


































