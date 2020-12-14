 /*prime算法每次将更新集合中到集合外的边，并将最短的边连接的节点加入集合
  * prime算法比kruskal算法更适合并行
  * N个节点需要N-1条边连接
*/


void primes(float **W,int **T,int N){
	int i,j,k;

	float *nearNode=new int[N];
	float *minDist=new float[N];

	float min;

	//从第0个节点开始,第0个点到其它点的距离
	for(i=1;i<N;i++){
		nearNode[i]=0;
		minDist[i]=w[i][0];
	}

	for (i=0;i<N-1;i++){
		min=FLT_MAX; //FLT_MAX在c++ .h被定义

//S1 找出计算最小距离点
//找minDist数组的最小的值，可并行化为reduce操作
//但不能直接用OpenMp reduction的min操作，不需要值,需要的是k
//可使用其它平台或自己实现，或自己实现此并行操作

		for(j=1;j<N;j++){
			if(0<=minDist[j]&&minDist<min)
			{
				min=minDist[j];
				k=j; //k is minindex 

			}
		}

//S2 加入Tree中
//只能串行
		T[i][0]=nearNode[k]; //(nearNode[k],k)一条边
		T[i][1]=k;

		minDist[k]=-1; //相当于删除此节点

		//加入了新点k,更新minDist

//S3 每个点计算更新距离
//每个j是独立的可并行
		for(j=1;j<N;j++){
			if(W[j][k]<minDist[j]){
				minDist[j]=W[j][k];
				nearNode[j]=k;
			}
		}
	}

	free(nearNode);
	free(minDist);
	return ;
}


