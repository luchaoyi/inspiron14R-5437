#include<stdio.h>
#include<string.h>
#include<errno.h>

//errno定义在errno.h中,保存了最近一次系统调用错误
int main(){
	int i;
	for(i=0;i<=255;i++){
		printf("%d:%s\n",i,strerror(i));
	}
	printf("%d\n",errno);
	return 0;
}

