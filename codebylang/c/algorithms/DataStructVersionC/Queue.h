//环形队列(循环队列)
//队列满则尾下标或尾指针下一个位置next就是头指针
//队列空则头==尾

//环形队列满时在增长
//若first 在last前面则简单复制到新空间  f->1  2 l->3   f->1 2 3 l->4
//若last在first前面则分别复制f->队列最大空间位置，然后复制l->f位置元素，可以使用出队列方法将数据就加入到新空间不复制

//STL::deque
//deque采用多个数组实现动态队列,多个数组使用一个map数组管理，将多个数组连接为一个逻辑连续的空间

//->空间连续可以是物理空间实际连续，也可以是逻辑(虚拟)的连续
//->关系可以是实际的直接的关系，也可以是虚拟的间接的关系







typedef struct{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;


typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

//带头好，便于处理边界
Status InitQuene(LinkQueue &Q)
{
	Q.rear=Q.front=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.rear) exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}

Status DestroyQuene(LinkQueue &Q)
{
	while(Q.rear!=Q.front)
	{
		p=Q.front->next->next;//~~~|
		free(Q.front->next);//     |
		Q.next=p;           //     |
	}							// |
	free(Q.front);               //|
							     //V
	//销毁时P指针可以由rear代劳没有用了
}

Status EnQuene(LinkQueue &Q,QElemType e){
	//链表头插入一样
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(OVERFLOW);
	p->data=e;
	Q->rear->next=p;
	Q.rear=p;
	return OK;
}


//可以考虑用一个指针将一些要删除的节点串起来组成空闲空间，预留
Status DeQueue(LinkQueue &Q,QElemType &e)
{
	if(Q.rear==Q.front) return ERROR;

	p=Q.front->next;
	Q.front->next=p->next;
	e=p->data;

	if(Q.rear == p) Q.rear=Q.front; //考虑结尾
	free(p);
	return OK;

	//谨慎考虑头尾边栏
}

//----------------------------------------------------
//循环队列 

#define MAXQSIZE 100

typedef struct{
	QElemType *base;
	int front;
	int rear;
	int elemNum;//元素个数
}SqQuene;

Status InitQuene(SqQuene &Q){
	Q.base=(QElemType*)malloc(sizeof(SqQuene)*MAXSIZE);
	if(!Q.base) exit(OVERFLOW);

	Q.front=Q.rear=0;
	Q.elemNum=0;

	return OK;
}

Status EnQuene(SqQuene &Q,QElemType e)
{

	if(elemNum==MAXQSIZE) return ERROR;
	Q.base[Q.rear]=e;
	Q.rear++;
	Q.elemNum++;
	if(Q.rear>=MAXQSIZE) Q.rear=Q.rear-MAXSIZE; //减与Mode效果一样

	return OK;
}

Status DeQueue(SqQuene &Q,QElemType &e)
{
	if(elemNum=0) return ERROR;
	e=Q.base[Q.front++];
	Q.elemNum--;
	if(Q.front>=MAXQSIZE) Q.front=Q.front-MAXSIZE;

	return OK;
}

inline int QueueLength(SqQuene Q)
{
	return Q.elemNum;
}

