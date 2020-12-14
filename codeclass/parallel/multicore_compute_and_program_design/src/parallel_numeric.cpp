//并行计算前缀和
//Parallel_PrefixSum额外的计算量比串行的多了不止一倍
//因此 Parallel_PrefixSum至少在4 Core 机器上才有实用价值


#include<omp.h>

void Parallel_PrefixSum(T *pInput,T* pOutput,int nLen)
{
	int i;
	int nCore=omp_get_num_procs();
//Parallel_PrefixSum额外的计算量比串行的多了不止一倍
//因此 Parallel_PrefixSum至少在4 Core 机器上才有实用价值
	if(nCore<4||nLen<MIN_PARALLEL_PREFIXSUM_COUNT){
		//串行
		//return 
	}


	//最后区间将所有包进去
	int nStep=nLen/nCore;
	if(nStep*nCore<nLen){
		nStep+=1
	}
/*
 *  1 3 4|5 7 8|10 9 2|7 9 12
 *s1 分组并行前缀和	 
 * 1 4 8|5 12 20|10 19 21|7 16 28
 *s2 串行，将每组最后一个值与后面最后一个值相加，其它值不变
 *     8    28=20+8   49=21+28  77=49+28       
 *s3第二组开始，每组除了最后一个值加前面的最后一个值
 * 1 4 8|5+8,12+8,28|10+28,19+28,49|7+49,16+49,77 
 * */


//step1
#pragma omp parallel for num_threads(nCore)
	for(i=0;i<nCore;i++){
		int nStart=i*nStep;
		int nEnd=(i+1)*nStep;
		if(nEnd>nLen)
		{
			nEnd=nLen;
		}
		pOutput[nStart]=pInput[nStart];
		int k;
		for(k=nStart+1;k<nEnd;k++){
			pOutput[k]=pOutput[k-1]+pInput[k];
		}
	}

//step2
	for(i=2;i<nCore;i++){
		pOutput[i*nStep-1]+=pOutput[(i-1)*nStep-1];
	}

//step3

#pragma omp parallel for num_threads(nCore-1)
	for(i=1;i<nCore;i++){
		int k;
		int nStart=i*nStep;
		int nEnd=(i+1)*nStep-1;
		if(nEnd>nLen)
		{
			nEnd=nLen;
		}
		for(k=nStart;k<nEnd;k++){
			pOutput[k]+=pOutput[nStart-1]
		}
	}
	return 
}




//矩阵乘法
//m*n*n*p = m*p

//c[i,j]=a[i,k]*b[k,j]
//以一行存储矩阵
void Matrix_Multiply(int *a,int row_a,int col_a,int *b,int row_b,int col_b,int *c,int c_size){
	if(col_a!=row_b || c_size<row_a*col_b) return;
	int i,j,k;

#pragma omp parallel for
	for(i=0;i<row_a;i++){
		int row_i=i*col_a;
		int row_c=i*col_b; //c is row_a*col_b
		for(j=0;j<col_b;j++){
			c[row_c+j]=0; //目标c位置
			for(k=0;k<row_b;k++){
				c[row_c+j]=a[row_i+k]*b[k*col_b+j];
			}
		}
	}


}

//改进，外两层合并
//扩大循环次数，核心较多时使用
void Parallel_Matrix_Multiply(int *a,int row_a,int col_a,int *b,int row_b,int col_b,int *c,int c_size){
	if(col_a!=row_b || c_size<row_a*col_b) return;
	int i,j,k;
	
	int index;
	int border=row_a*row_b;
	i=0;j=0;

#pragma omp parallel for private(i,j,k) num_threads(dtn(border,1))
	for(index=0;index<border;index++){
		i=index/col_b;   //index point c //rowc=index/col_b ,col_c=index%colb
		j=index%colb;

		//下标计算
		int row_i=i*col_a;
		int row_c=i*col_b;
		c[row_c+j]=0;

		for(k=0;k<row_b;k++){
			c[row_c+j]=a[row_i+k]*b[k*col_b+j];
		}
	}

}









