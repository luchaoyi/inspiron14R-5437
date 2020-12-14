



typedef struct DulNde
{
    DataType data;

    pNode prior,next;


}NOde,*pNOde;



void Insert(PNode first,int i,DataType x)
{
    q=first;

    count=0;

    while(q!=NULL&&count<i-1)
    {
        q=q->next;
        count++;
    }
    //工作指针后移到插入位置

    //if判断q是否有效

    p=(pNode)malloc(sizeof(Node));

    p->data=x;

    //先安排申请节点节省了临时变量保存

    p->prior=q;
    p->next=q->next;

    q->next->prior=p;

    q->netx=p;
}


void Delete(PNode first,int i,DataType x)
{


    //p为工作指针

    temp=q;//暂存q

    q->prior->next=q->next;
    q->next->prior=q->prior;

    free(temp);
}





























