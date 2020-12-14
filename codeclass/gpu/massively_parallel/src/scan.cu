//串行scan
//双精度的sum可以避免累加误差
void scan(float *x,float *y,int Max_i){
	double sum;
	sum=x[0];
	for(i=1;i<Max_i;i++){
		sum+=x[i];
		y[i]=sum;
	}
}




//跳步scan
//开始累加相邻元素，
//然后累加相隔2元素
//...stride*=2

__global__  stride_scan(float *X,float *Y,int InputSize){
	__shared__ float XY[SECTION_SIZE];//每一个block内的scan
	int i=blockIdx.x+blockDim.x+threadIdx.x;
	if(i<InputSize){
		XY[threadIdx.x]=X[i];
	}
	
	//scan on XY

	for(unsigned int stride=1;stride<=threadIdx.x;stride*=2){
		__syncthreads();
		XY[threadIdx.x]+=XY[threadIdx.x-stride];
	}
	Y[i]=XY[i];
}


//归约树
//先归约，在倒过来分发
__global__  tree_reduce_scan(float *X,float *Y,int InputSize){

	int i=blockIdx.x+blockDim.x+threadIdx.x;
	if(i<InputSize){
		XY[threadIdx.x]=X[i];
	}

	for(unsigned int stride=1;stride<=blockDim.x;stride*=2){
		__syncthreads();
		int index=(threadIdx.x+1)*2*stride-1;

		if(index<blockDim.x){
			XY[index]+=XY[index-stride];
		}

	for(int stride=SECTION_SIZE/4;stride>0;stride/=2){
		__syncthreads();
		int index=(threadIdx.x+1)*stride*2-1;
		if(index+stride<BLOCK_SIZE)
		{
			XY[index+stride]++XY[index];
		}
	}

	__syncthreads();
	Y[i]=XY[threadIdx.x];
}
}

//任意长度的scan，可以分段采用上述方法scan
//然后将每段最后一个元素scan
//然后每段加上scan后的数组







