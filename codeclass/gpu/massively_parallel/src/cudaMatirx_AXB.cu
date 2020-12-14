//使用二维Grid将矩阵分成一个个block方块
//block方块是二维block,每一个线程负责计算一个元素
//C[i][j]= 对k循环求和 A[i][k]*B[k][j]


//Width * Width 方阵
//Idx Index


__global__ void MatrixMulKernel(float * d_M,float * d_N,float * d_P,int Width)
{
	//blockIdx内置dim3变量，每个线程有自己的blockIdx和threadIdx用于定位
	int Col=blockIdx.x*blockDim.x+threadIdx.x;
	int Row=blockIdx.y*blockDim.y+threadIdx.y;

	if(Row<Width) && (Col<Width) {
		float Pvalue=0;
		for(intk=0;intk<Width;intk++){
			Pvalue=d_M[Row*Width+k]*d_N[k*Width+Col];
		}
		d_P[Row*Width+Col] = Pvalue;
	}
}


//矩阵以行优先(连续)或列优先(连续)存储
//A X B 时 A的一行*B的一列，必定有一个不满足连续访存
//因此对另一个进行转置让其满足矩阵乘法


//使用共享存储器加载分块优化全局访问的矩阵乘法
#define TILE_WIDTH 16
__global__ void MatrixMulKernel(float * d_M,float * d_N,float * d_P,int Width){
	__shared__ float Mds[TILE_WIDTH][TILE_WIDTH];
	__shared__ float Nds[TILE_WIDTH][TILE_WIDTH];

	int bx=blockIdx.x;int by=blockIdx.y;
	int tx=threadIdx.x;int ty=threadIdx.y;

	//一个block共享 __shared__,因此一个block负责一个块,块大小为TILE_WIDTH
	int Row=by*TILE_WIDTH+ty;
	int Col=bx*TILE_WIDTH+tx;

	float Pvalue=0;
	for(int m=0;m<Width/TILE_WIDTH;++m){
		//一块一块加载元素，一块一块计算
		Mds[ty][tx]=d_M[Row*Width+m*TILE_WIDTH+tx];
		Nds[ty][tx]=d_N[(m*TILE_WIDTH+ty)*Width+Col];
		__syncthreads();

		for(int k=0;k<TILE_WIDTH;++k){
			Pvalue+=Mds[ty][k]*Nds[k][tx];
		}
		__syncthreads();
	}

	d_P[Row*Width+Col]=Pvalue;
}
