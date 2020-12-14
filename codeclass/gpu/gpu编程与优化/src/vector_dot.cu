//c=A.B
//求和累加

//不同线程计算乘积,然后在求和归约
__global__ void vdp_1(DATATYPE *a,DATATYPE *b,DATATYPE *c,int n){
	__shared__ DATATYPE tmp[threadnum];

	const int tidx=threadIdx.x;
	const int t_n=blockDim.x;

	int tid=tidx;
	double tmp=0.0;

	//t_n不一定等于n,一个线程可能计算多个元素
	while(tid<n){
		temp+=a[tid]*b[tid];
		tid+=t_n;
	}
	tmp[tidx]=temp;
	__syncthreads();


	int i=2,j=1;

	while(i<threadnum){
		if(tidx%i==0){
			tmp[tidx]+=tmp[tid+j];
		}
		__syncthreads();
		i*=2;
		j*=2;
	}


	if(tidx==0){
		c[0]=tmp[0];
	}

//vdp_1<<<1,threadnum>>>(...) 单block
}

//可以使用多个block 
//可以GPU初步归约后
//发送到CPU，CPU再次归约
