#include<stdio.h>


struct Node
{
	DataType data;
	Node *next;

}Node,*pNode;

struct 
{
	Node *front,*rear;
}lq,plq;


void InitQuene(plq Q)
{
	//用头结点数据域记录队列个数
	p=(pNode)malloc(sizeof(Node));
	p->data=0;
	p->next=NULL;
	Q->rear=Q->front=p;
}

void EnQuene(plq Q,DataType x)
{
	p=(pNode)malloc(sizeof(Node));
	p->data=x;
	p->next=NULL;


	
	//将入队元素链接在队尾
	Q->rear->next=p;
	//尾指针指向新队尾元素
	Q->rear=p;

	++Q->front->data;
}

//出队
DataType DeQuene(plq Q)
{
	if(Q->front->data==0)
		//Q->front==Q->rear
	ptemp=Q->front->next;
	temp=Q->front->data;

	Q->front->next=Q->front->next->next;
	free(ptemp);
	return temp;
}
