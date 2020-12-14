void InsertionSort(int *A,int N){
	int i,j,v;

	for(i=1;i<N;i++){
		v=A[i];
		j=i;
		while(A[j-1]>v)
		{
			A[j]=A[j-1];
			j--;
			if(j<=0) break;
		}
		A[j]=v;
	}
}


/*
 *希尔排序对排序进行优化
 *跳跃式排序从h个跨度开始,多个一组，排序，指定h=1对所有排序一次
 *每一个跳跃组独立，可并行排序
 * 0 1 2 3 4 5 6 7 8 9 
 * e.g. h=3
 * 独立为组
 * 0 3 6 9 | 1 4 7| 2 5 8 
 * */


void parallelShellSort(int *A,int N){
	int k,h;

	h=1;while(h<N) h=3*h+1;
	h/=3;

#pragma omp parallel firstprivate(h)
{
	while(h!=1){
#pragma omp for
		for(k=0;k<h;k++){
			v=A[i];
			j=i;
			while(A[j-h]>v){
				A[j]=A[j-h];
				j-=h;
				if(j<=h) break;
			}
			A[j]=v;
		}
	}
	h/=3;
}
//h=1所有都为一组
InsertionSort(A,N);
}
