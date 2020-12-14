#include<stdio.h>
#include<mpi.h>
#include<math.h>


double f(double x){
	return 4.0/(1.0+x*x);
}

//计算1/N*sum(i=1 to N)f((i-0.5)/N)

int main(int argc,char** argv){
	//定义的所有变量，每个进程都有一个副本，不能互相访问
	int myid;
	int numprocs;

	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int namelen;

	double startwtime,endwtime;
	int N=0;
	double h;//h=1/N
	double sum;

	double x;
	double pi;
	double mypi;

	int i;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Get_processor_name(processor_name,&namelen);

	fprintf(stdout,"process %d of %d on %s\n",myid,numprocs,processor_name);

	if(myid==0){
		printf("Please give N=");
		scanf("%d",&N);
		startwtime=MPI_Wtime();
	}
	MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD); //广播N
	h=1.0/(double)N;
	sum=0.0;

	//每个进程算一部分
	//如myid==0,numprocs=4,则i=1,5,9,...
	for(i=myid+1;i<=N;i+=numprocs){
		x=h*((double)i-0.5);
		sum+=f(x);
	}
	mypi=h*sum;

	//把每个进程mypi的值reduce后发送到root的pi
	MPI_Reduce(&mypi,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

	if(myid==0){
		printf("pi is %.64f\n",pi);
		endwtime=MPI_Wtime();
		printf("wall clock time=%f\n",endwtime-startwtime);
		fflush(stdout);
	}

	MPI_Allreduce(&mypi,&pi,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
	printf("id:%d,pi:%.64f\n",myid,pi);


	MPI_Finalize();
	return 0;
}

