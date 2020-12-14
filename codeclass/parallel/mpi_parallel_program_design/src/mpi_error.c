#include<stdio.h>
#include<mpi.h>




//MPI调用出错时会返回一个错误码

//MPI_ERROR_STRING(int errorcode,char* string,int strlen)根据提供错误码得到一个字符串，对错误码更多的说明
//MPI_ERROR_CLASS(int errorcode,int *errorclass)将一个错误码转换为一个小的被说明值之一，称为错误类。
//如:
//MPI_SUCCESS 无错误
//MPI_ERR_BUFFER 无效缓冲区指针
//MPI_ERR_COUNT 无效计数参数
//MPI_ERR_TYPE 无效数据类型参数

//还可以定义错误代码处理函数，向MPI系统注册后可以使用

int main(int argc,char** argv){
	int rank;
	char s[MPI_MAX_ERROR_STRING];
	int slen;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank==0){
		printf("MPI_SUCESS:%d\n",MPI_SUCCESS);
		printf("MPI_ERR_BUFFER:%d\n",MPI_ERR_BUFFER);
		printf("MPI_ERR_COUNT:%d\n",MPI_ERR_COUNT);
		printf("MPI_ERR_TYPE:%d\n",MPI_ERR_TYPE);
		
		//MPI_Error_string也可接收一个错误类
		MPI_Error_string(MPI_ERR_BUFFER,s,&slen);
		printf("%s\n",s);
	}


	MPI_Finalize();
	return 0;
}

