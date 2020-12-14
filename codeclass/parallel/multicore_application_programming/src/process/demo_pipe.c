#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
	int status;
	int pipes[2];
	pipe(pipes);

	pid_t pid =fork();

//从写入端写入内容从读取端读取
//返回的是两个文件描述符

	if(pid == 0){
		close(pipes[0]); //读取端
		write(pipes[1],"a",1);//写入端
		printf("Child sent 'a'\n");
		close(pipes[1]);
	}
	else
	{
		char buffer[11];
		close(pipes[1]);
		int len=read(pipes[0],buffer,10);
		buffer[len]=0;
		printf("Parent received %s\n",buffer);
		close(pipes[0]);
	}

	demo_mknod();
	return 0;
}


/*
//命名管道
void demo_mknod(){
	int status;
	//创建一个命名管道，然后可以使用open像使用文件一样使用它
	mknod("/tmp/pipefile",S_IFIFO|S_IRUSR|S_IWUSR,0);
	pid_t f=fork();
	if(f==0)
	{
		int mypipe=("/tmp/pipefile",O_WRONLY);//open and write
		write(mypipe,"a",1);
		close(mypipe);
	}
	else
	{
		int mypipe=open("/tmp/pipefile",O_RDONLY);
		char buffer[11];
		int len=read(mypipe,buffer,10);
		buffer[len]=0;
		printf("received %s\n",buffer);
		close(mypipe);
	}
	unlink("/tmp/pipefile");
	return;
}
*/
