//CSR
//r=Ax
inline void smmSerial(const int numRows,const int *rowOffset,const int *columnIndex,const float* val,const float *x,float *r){
	int rowStart;
	int rowEnd;

	for(i=0;i<numRows;i++){
		rowStart=rowOffset[i];
		rowEnd=rowOffset[i+1];
		float sum=0.0f;

		for(j=rowStart;j<rowEnd;j++)
		{
			sum+=val[j]*x[columnIndex[j]];
		}

		r[i]=sum;
	}
}

//openmp 动态调度，行长度不一样
#pragma omp parallel for private(rowStart,rowEnd) schedule(dynamic:size)
	for(i=0;i<numRows;i++){
		...
	}


//cuda
//矩阵每行元素数量不一致，怎样更合理划分.
//自适应算法
//对行以非零元数目排序，非零元数目接近的可以在一个内核处理(或在一个wrap?)




//对称矩阵乘法，只需保存矩阵上/下三角
//可以一维数组存储三角矩阵
inline void getSysRowCol(int row,int col,int *t_row,int *t_col){
	*t_row=row>col?row:col;
	*t_col=row>col?col:row;
}

void symv(...){
	for(row=0;row<numRows;row++){

		for(col=0;col<n;col++){
			getSysRowCol(...);
			sum+=mat[t_row*(t_row+1)/2+t_col]*v[col];
		}
	}
}







