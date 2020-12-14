/*************************************************************************
    > File Name: mpi_hello.c
    > Author: lcy
    > Mail: 751714700@qq.com 
    > Created Time: 2017年03月02日 星期四 22时23分15秒
 ************************************************************************/

#include<stdio.h>
#include<mpi.h>
#include<string.h>

//mpicc mpi_hello.c -o mpi_hello
//mpiexec -n 4 ./mpi_hello

int main(int argc,char * argv[])
{
	int myid,numprocs;
	int namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	char message[20];
	MPI_Status status;
	
	int version,subversion;
	int flag;


//必须	以MPI_Init开始	以MPI_Finalize()结束

	MPI_Initialized(&flag); //唯一用在MPI_Init前的函数，用于判断是否初始化
	printf("%d\n",flag);

	MPI_Init(&argc,&argv);

	//获得进程信息,id,处理器个数等
	//openMp有类似函数
	MPI_Comm_rank(MPI_COMM_WORLD,&myid); //获取进程标识
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
//processor_name 机器名 lcy
	MPI_Get_processor_name(processor_name,&namelen);
	MPI_Get_version(&version,&subversion); //获取版本
	
	//printf("namelen %d\n",namelen);
	printf("Process %d of %d on %s,mpi version:%d.%d\n",myid,numprocs,processor_name,version,subversion);
	
	MPI_Barrier(MPI_COMM_WORLD); //在此同步

	if(myid==0)
	{
		printf("only 0 exec\n");
		strcpy(message,"Hello,Process 0");
		//dest=1,tag=99
		MPI_Send(message,strlen(message)+1,MPI_CHAR,1,99,MPI_COMM_WORLD); 

	}

	if(myid==1)
	{
		printf("only 1 exec \n");
		//maxlen=20,src=0,tag=99 status保存状态信息
		MPI_Recv(message,20,MPI_CHAR,0,99,MPI_COMM_WORLD,&status);
		printf("Recv:%s\n",message);

		MPI_Send(message,strlen(message)+1,MPI_CHAR,2,99,MPI_COMM_WORLD); 
	}


	MPI_Finalize();

	return 0;
}

