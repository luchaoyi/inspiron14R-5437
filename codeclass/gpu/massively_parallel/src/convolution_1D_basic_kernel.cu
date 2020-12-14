//N is input
//M is卷积模板
//P is output

__global__ void convolution_1D_basic_kernel(float *N,float *M,float *P,int Mask_width,int width){

	//线程内使用寄存器存储变量
	//避免多次访问全局存储器
	int i=blockIdx.x*blockDim.x+threadIdx.x;

	float Pvalue=0;
	int N_start_point=i-(Mask_width/2);

	for(j=0;j<Mask_width;j++){
		if(N_start_point+j>=0 && N_start_point+j<=Width){
			Pvalue+=N[N_start_point+j]*M[j];
		}
	}

	P[i]=Pvalue;

}

//=>优化

//卷积核M不改变，且一般相对于N很小
//使用常数存储器存储

#define MAX_MASK_WIDTH 10
__constant__ float M[MAX_MASK_WIDTH];
cudaMemcpyToSymbol(M,h_M,Mask_width*sizeof(float));  //主机h_M->M 复制数据到常数存储器

//代码没有改动只是使用常数存储器存储了M 
//常数存储器速度不比全局存储器快，但它存储的值不变，因此GPU可以将它直接加载到高速缓存中(高速缓存是透明的,程序不操作它),不会出现不一致问题

__global__ void convolution_1D_basic_kernel(float *N,float *P,int Mask_width,int width){

	//线程内使用寄存器存储变量
	//避免多次访问全局存储器
	int i=blockIdx.x*blockDim.x+threadIdx.x;

	float Pvalue=0;
	int N_start_point=i-(Mask_width/2);

	for(j=0;j<Mask_width;j++){
		if(N_start_point+j>=0 && N_start_point+j<=Width){
			Pvalue+=N[N_start_point+j]*M[j];
		}
	}

	P[i]=Pvalue;

}



//分块卷积，每个block负责一个分块，每个thread负责分块内的每个元素
//共享存储器是block共享，不同block私有,使用共享存储器存储每个block负责的分段的元素，减少直接访问全局存储N

//cuda编程与host编程不同，会经常声明变量存储中间结果为为了使用寄存器加快速度.

#define TILE_SIZE 分块大小

__global__ void convolution_1D_basic_kernel(float *N,float *P,int Mask_width,int width){
	int i=blockIdx.x*blockDim.x+threadIdx.x;  //一维block,每个block内是一维thread 


	__shared__ float N_ds[TILE_SIZE]; //共享存储器是block私有的
	N_ds[threadIdx.x]=N[i]; //将每段元素先载入到共享存储中,每个线程载入一个

	__syncthreads(); //同步等待block内线程都已载入元素

	int This_tile_start_point = blockIdx.x*blockDim.x;
	int Next_tile_start_point=This_tile_start_point+blockDim.x;//next=(this+1)*len
	int N_start_point=i-(Mask_width/2); //此线程计算元素，卷积开始位置
	float Pvalue=0;

	
	for(int j=0;j<Mask_width;j++){
		int N_index=N_start_point+j;
		if(N_index>=0&&N_index<width){ //在此区域外补0,不算
			if(
					(N_index>=This_tile_start_point) 
					&&
					(N_index<Next_tile_start_point)
					)//元素在此段内，则存储在共享存储器中
				Pvalue+=N_ds[threadIdx.x+j-(Mask_width/2)]*M[j];
			else

			/*书中提到的复杂的分块卷积，是将这些光环元素，即对于此分块的边界元素也加载到了共享存储器中,这样需要更多的控制逻辑.
			这里利用了一个事实是N元素可能已经被加载到了高速缓存,因此并不会频繁从N加载
			*/
				Pvalue+=N[N_index]*M[j];  //没在则从N中加载
		}
	}
}
