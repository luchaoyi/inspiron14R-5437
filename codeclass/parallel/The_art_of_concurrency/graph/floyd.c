void Floyds(float **D,int N){
	int i,j,k;
	for(i=0;k<N;k++){
#pragma omp parallel for 
		for(i=0;i<N;i++){
			for (j=0;i<N;j++){
				//D[i][j]与D[k][j]不存在竞争
				//考虑更新D[i][j]时D[k][j]被其它更新
				//D[k][j]=min(D[k][j],D[k][k]+D[k][j])
				//除非D[k][k]<0否则不会出现
				D[i][j]=min(D[i][j],D[i][k]+D[k][j]); 
			}
		}
	}

}

/*floyd 算法适合共享内存，若使用分布式内存如MPI等
 * 则更适合使用dijstra，每一线程独立计算一个节点
 * /
