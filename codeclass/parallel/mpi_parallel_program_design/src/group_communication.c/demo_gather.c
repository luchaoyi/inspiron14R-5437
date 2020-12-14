#include<stdio.h>
#include<mpi.h>


//Gather 多对一,多个进程类型和长度相同
//Gatherv 可接受不同长度数据,类型一致
//Gather*逆操作
//Scatter
//Scatterv 

int main(int argc,char** argv){
	int rank;
	int gsize;
	int sendarray[100];
	int *rootbuf;
	int rootid;
	...
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	rootbuf=(int *)malloc(sizeof(int)*100*gsize);
	//每个进程发送100个长度的int,接受进程从每一个接收100个int
	MPI_Gather(sendarray,100,MPI_INIT,rootbuf,100,root,MPI_COMM_WORLD);

	MPI_Finalize();
	return 0;
}

