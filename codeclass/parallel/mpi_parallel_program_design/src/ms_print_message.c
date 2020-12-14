#include<mpi.h>
#include<stdio.h>

int main(int argc,char **argv){
	int rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank==0){
		master_io();
	}else
	{
		slave_io(rank);
	}
	MPI_Finalize();
}


//定义消息标识
#define MSG_EXIT 1
#define MSG_PRINT_ORDERED 2 /*按序打印的消息*/
#define MSG_PRINT_UNORDERED 3 /*乱序打印的消息*/


int master_io(){
	int i,j,size,nslave,firstmsg;
	char buf[256],buf2[256];
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	nslave=size-1;
	while(nslave>0){
		MPI_Recv(buf,256,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
		switch(status.MPI_TAG){
			case MSG_EXIT:
				nslave--;
				break;
			case MSG_PRINT_UNORDERED:
				fputs(buf,stdout);
				break;
			case MSG_PRINT_ORDERED://按序打印的消息，符合顺序则直接打印，不符合则需要缓存
				firstmsg=status.MPI_SOURCE;
				for(i=1;i<size;i++){ // 若是第i个进程的消息，则直接打印，否则接受第i个消息
					if(i==firstmsg)
						fputs(buf,stdout);
					else
					{
						MPI_Recv(buf2,256,MPI_CHAR,i,MSG_PRINT_ORDERED,MPI_COMM_WORLD,&status);
						fputs(buf2,stdout);
					}
				}
				break;
		}
	}

}

int slave_io(int rank){
	char buf[256];

	//两个有序，一个无序，一个退出
	sprintf(buf,"hello from slave %d,ordered print\n",rank); //字符串->buf
	//send ordered message to master process whose id is 0
	MPI_Send(buf,strlen(buf)+1,MPI_CHAR,0,MSG_PRINT_ORDERED,MPI_COMM_WORLD);
	sprintf(buf,"goodbye from slave %d,ordered print\n",rank); //字符串->buf
	MPI_Send(buf,strlen(buf)+1,MPI_CHAR,0,MSG_PRINT_ORDERED,MPI_COMM_WORLD);

	sprintf(buf,"I am exiting %d,unordered print\n",rank); //字符串->buf 
	MPI_Send(buf,strlen(buf)+1,MPI_CHAR,0,MSG_PRINT_UNORDERED,MPI_COMM_WORLD); 


	MPI_Send(buf,strlen(buf)+1,MPI_CHAR,0,MSG_PRINT_UNORDERED,MPI_COMM_WORLD);
	MPI_Send(buf,0,MPI_CHAR,0,MSG_EXIT,MPI_COMM_WORLD);
}
