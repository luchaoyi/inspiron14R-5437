#include<cuda.h>
#include<stdio.h>


//device is SPMD so all线程执行同一份代码
//调用kernel函数会在device生成线程网格，一个网格是包含多个线程的线程块
//每个线程块内的线程由threadIdx标识
//每一个线程块由blockIdx标识,块内线程数blockDim
__global__ void vecAddKernel(float *A,float *B,float *C,int n){
	//因此每一个线程计算的i是唯一的
	int i=blockIdx.x*blockDim.x+threadIdx.x; 
	//可以以此i当作下标
	if(i<n) C[i]=A[i]+B[i];
}



//使用二维网格处理二维图片
__global__ void PictureKernel(float *d_Pin,float *d_Pout,int n,int m){
	int Row=blockIdx.y*blockDim.y+threadIdx.y;
	int Col=blockIdx.x*blockDim.x+threadIdx.x;
	if((Row<m)&&(Col<n)){
		d_Pout[Row*n+Col]=2*d_Pin[Row*n+Col];
	}

}




__host__ void vecAdd(float *A,float *B,float *C,int n) //激活__global__函数的__host__函数，称为stub函数
{
	int size=n*sizeof(float);
	float *d_A,*d_B,*d_C;


	cudaMalloc((void **)&d_A,size);
	//destination,source,bytes?,->?
	cudaMemcpy(d_A,A,size,cudaMemcpyHostToDevice);
	cudaMalloc((void **)&d_B,size);
	cudaMemcpy(d_B,B,size,cudaMemcpyHostToDevice);
	cudaMalloc((void **)&d_C,size);

	//激活kernel函数,在device执行向量运算
	//<<<block的number,block的线程数>>>



	dim3 dimGrid(ceil(n/256.0),1,1);
	dim3 dimBlock(256,1,1);
	vecAddKernel<<<dimGrid,dimBlock>>>(d_A,d_B,d_C,size);
	//vecAddKernel<<<ceil(n/256.0),256>>>(d_A,d_B,d_C,size);
	//回收result
	//d_C->C
	cudaDeviceSynchronize();
	cudaMemcpy(C,d_C,size,cudaMemcpyDeviceToHost);
	//Free device
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);

}

#define N 1000

int main(int argc,char** argv){

	float A[N];
	float B[N];
	float C[N];
	int i;


	for(i=0;i<N;i++){
		A[i]=1.0;
		B[i]=2.0;
		C[i]=0.0;
	}
	

	vecAdd(A,B,C,N);
	for(i=0;i<N;i++){
		printf("%f\n",C[i]);
	}
	
	return 0;
}



