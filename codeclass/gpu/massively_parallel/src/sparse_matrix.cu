//串行
//A*x+y 矩阵×向量+向量

//A=
//row_ptr
//data
//col_index

void SPMV_CSR()
{

for (int row=0;row<num_rows;row++){
	float dot=0;
	int row_start=row_ptr[row];
	int row_end=row_ptr[row+1];

	for(int elem=row_start;elem<row_end;elem++){
		dot+=data[elem]*x[col_index[elem]];

	}
	y[row]+=dot;
}
}

//并行化
//每一行dot是独立的 A[i]*x+y独立


__global__ void SPMV_CSR(int num_rows,float *data,int *col_index,
		int *row_ptr,float *x,float *y
		){

	int row=blockIdx.x*blockDim.x+threadIdx.x;

	if(row<num_rows){
		float dot=0;
		int row_start=row_ptr[row];
		int row_end=row_ptr[row+1];

		for(int elem=row_start;elem<row_end;elem++){
			dot+=data[elem]*x[col_index[elem]];

		}
		y[row]+=dot;
	}
}




//填充与转置
//行长短不一样，则wrap内线程迭代次数不一致,可以填充元素使行一样长消除控制流分支
//合并访问
//每一个线程访问A的不同行执行dot运算
//若按列存储则不同行同一列元素相邻存储，则相邻线程访问相邻元素可以合并访问,优化速度

//排序划分
//为使wrap尽量对齐，可以按行元素数量对矩阵排序，将元素数量接近的划分到一个段，为每一个段构造一个kernel或在一个block内处理
//在如线性方程求解等问题上，行互换是不影响结果的
//在影响结构的问题上需要记录行原来所属位置


