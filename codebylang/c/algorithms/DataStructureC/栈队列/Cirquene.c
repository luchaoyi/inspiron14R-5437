#include<stdio.h>

typedef struct 
{
	DataType data[MAX_SIZE];//缓冲区最大空间
	int front,rear;
}CirQueue;

//解决假溢出问题使用循环队列

void InitQuene()
{
	//Q.front = Q.rear = 0
	Q.front = Q.rear = MAX_SIZE-1;
	//使用一端
}

//头尾指针向一个方向移动保证先入先出
//头尾指针同向圆周运动当头==尾说明相撞


void EnQuene()
{

	
	//尾走，尾入，尾撞头，队满

	//空一格间距利于判断

	if((Q.rear+1)%MAX_SIZE==Q.front)//当尾在走一步时就会撞已满
		printf(error!);

	Q.rear=(Q.rear+1)%MAX_SIZE;
	Q.data[Q.rear]=x;
}

//*****************************//


DataType DeQuene()
{
	//此队头指针滞后一格，所以每次队头指针先移动一格才指向队头将出队元素

	//头走，头出，头==尾时是队空状态，
	if((Q.front==Q.rear)
		//error
	
	Q.front=(Q.front+1)%MAX_SIZE;

	return Q.data[Q.front];
}

//读取队头不改变指针
DataType GetFront()
{
	if((Q.front==Q.rear)
		//error
	
	i=(Q.front+1)%MAX_SIZE;

	return Q.data[i];

}
bool Empty()
{
	//Q.rear == Q.front
}