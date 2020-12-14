#include<unistd.h>
#include<signal.h>
#include<setjmp.h>

static jmp_buf env_alrm;
static void sig_alrm(){
	longjmp(env_alrm,1);
}

unsigned int sleep2(unsigned int senconds){
	if (signal(SIGALRM,sig_alrm)==SIG_ERR)
		return senconds;

	if(setjmp(env_alrm)==0){
	alarm(senconds);//设置定时器，由内核向进程发送SIGALRM信号
	pause();//阻塞直到从一个信号处理函数返回，pause才返回	
}
	return (alarm(0)); //trun off timer

}

int main(){
	sleep2(5);
	return 0;
}
