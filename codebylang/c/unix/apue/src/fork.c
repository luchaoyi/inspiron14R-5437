#include<unistd.h>
#include<stdio.h>


int main(){
	pid_t pid=fork();

	if(pid<0){
		printf("Fork Error\n");
	}
	else if(pid>0){
		printf("P\n");
	}
	else
	{
		printf("S\n");
	}
return 0;
}

