#include<mqueue.h>
#include<stdio.h>
#include<unistd.h> //unix stdio
#include<string.h>

int main()
{
	int status;
	pid_t pid=fork();

	if(pid==0)
	{
		//Sub
		mqd_t *queue;
		char message[20];
		queue = mq_open("/message",O_WRONLY+O_CREAT,0777,0);
		strncpy(message,"Hello",6);
		printf("Send message %s\n",message);
		//message copy to queue
		mq_send(queue,message,strlen(message)+1,0);
		mq_close(queue);
		printf("Child process completed\n");
	}
	else
	{
		//Parent 
		sleep(5);
		mqd_t *queue;
		char message[20];
		queue=mq_open("/message",O_RDONLY+O_CREAT,0777,0);
		mq_receive(queue,message,2000,0);
		printf("Receive message %s\n",message);
		mq_close(queue);
		mq_unlink("/message");
		printf("Parent process completed\n");
	}
	return 0;
}


