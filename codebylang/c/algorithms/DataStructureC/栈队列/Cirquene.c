#include<stdio.h>

typedef struct 
{
	DataType data[MAX_SIZE];//���������ռ�
	int front,rear;
}CirQueue;

//������������ʹ��ѭ������

void InitQuene()
{
	//Q.front = Q.rear = 0
	Q.front = Q.rear = MAX_SIZE-1;
	//ʹ��һ��
}

//ͷβָ����һ�������ƶ���֤�����ȳ�
//ͷβָ��ͬ��Բ���˶���ͷ==β˵����ײ


void EnQuene()
{

	
	//β�ߣ�β�룬βײͷ������

	//��һ���������ж�

	if((Q.rear+1)%MAX_SIZE==Q.front)//��β����һ��ʱ�ͻ�ײ����
		printf(error!);

	Q.rear=(Q.rear+1)%MAX_SIZE;
	Q.data[Q.rear]=x;
}

//*****************************//


DataType DeQuene()
{
	//�˶�ͷָ���ͺ�һ������ÿ�ζ�ͷָ�����ƶ�һ���ָ���ͷ������Ԫ��

	//ͷ�ߣ�ͷ����ͷ==βʱ�Ƕӿ�״̬��
	if((Q.front==Q.rear)
		//error
	
	Q.front=(Q.front+1)%MAX_SIZE;

	return Q.data[Q.front];
}

//��ȡ��ͷ���ı�ָ��
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