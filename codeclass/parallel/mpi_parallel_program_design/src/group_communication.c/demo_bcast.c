#include<stdio.h>
#include<mpi.h>


int main(int argc,char** argv){
	int rank;
	int value;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	do{
		//Master Bcast
		if(rank==0){
			scanf("%d",&value);
		}
		//广播操作，将&value缓冲区内容复制到COMM中包括自己的所有进程的&value缓冲区中
		MPI_Bcast(&value,1,MPI_INT,0,MPI_COMM_WORLD);
		printf("Process %d got %d\n",rank,value);//各进程打印的广播消息
	}while(value>=0);

	MPI_Finalize();
	return 0;
}

