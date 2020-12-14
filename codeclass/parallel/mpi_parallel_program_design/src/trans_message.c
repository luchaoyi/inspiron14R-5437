#include<stdio.h>
#include<mpi.h>
#include<string.h>

int main(int argc,char *argv[])
{
	int pid;
	int size;
	char message[20];
	MPI_Status status;

	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&pid);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(pid==0){
		strcpy(message,"!@#$%^&*");
		MPI_Send(message,strlen(message)+1,MPI_CHAR,1,99,MPI_COMM_WORLD);
		printf("send %s %d -> %d\n",message,pid,pid+1);
	}
	else
	{
		if(pid!=(size-1))
		{
			//status 由 MPI_SOURCE,MPI_TAG,MPI_ERROR组成
			MPI_Recv(message,20,MPI_CHAR,pid-1,99,MPI_COMM_WORLD,&status);
			printf("%d recv <%s> from %d\n",pid,message,status.MPI_SOURCE);
			//pid-1 -> pid -> pid+1
			MPI_Send(message,strlen(message)+1,MPI_CHAR,pid+1,99,MPI_COMM_WORLD);
			printf("send %s %d -> %d\n",message,pid,pid+1);
		}
		else
		{
			MPI_Recv(message,20,MPI_CHAR,pid-1,99,MPI_COMM_WORLD,&status);
			printf("%d recv <%s> from %d\n",pid,message,status.MPI_SOURCE);
		}
	}

	MPI_Finalize();
	return 0;
}
