#include<mpi.h>
#include<stdio.h>
#include<math.h>

double f(double);

double f(double a){
	return (4.0/(1.0+a*a));
}


int main(int argc,char *argv[]){
	int n,myid,numprocs,i;

	double mypi,pi,h,sum,x;
	double startwttime=0.0,endwttime;
	int namelen;
	char process_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Get_processor_name(process_name,&namelen);

	printf("%d,%d,%s\n",myid,numprocs,process_name);

	n=10000;

	if(myid==0)
		startwttime=MPI_Wtime();

	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	h=1.0/(double) n;
	sum=0.0;

	for(i=myid+1;i<=n;i+=numprocs){
		x=h*((double)i-0.5);
		sum+=f(x);
	}
	mypi=h*sum;

	MPI_Reduce(&mypi,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

	if(myid==0){
		endwttime=MPI_Wtime();
		printf("pi is %.20f\n",pi);
		printf("wall clock time=%f\n",endwttime-startwttime);
	}

	MPI_Finalize();
	return 0;
}
