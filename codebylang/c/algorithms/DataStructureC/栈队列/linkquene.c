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
	//��ͷ����������¼���и���
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


	
	//�����Ԫ�������ڶ�β
	Q->rear->next=p;
	//βָ��ָ���¶�βԪ��
	Q->rear=p;

	++Q->front->data;
}

//����
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
