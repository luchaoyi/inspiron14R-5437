#include<stdio.h>
#include<mpi.h>


int main(int argc,char** argv){
	int a=0;
	int b=1;
	int c=2;
	MPI_Aint indices; //MPI_Aint may is int

	MPI_Init(&argc,&argv);
	
	//MPI_Address返回相对于一个预定义地址(参照物,like 坐标轴0)的偏移量
	MPI_Address(&a,&indices);
	printf("%d\n",(int)indices);

	MPI_Address(&b,&indices);
	printf("%d\n",(int)indices);

	MPI_Address(&c,&indices);
	printf("%d\n",(int)indices);

	MPI_Finalize();
	return 0;
}

