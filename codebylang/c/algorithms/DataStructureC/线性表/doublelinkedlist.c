



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
    //����ָ����Ƶ�����λ��

    //if�ж�q�Ƿ���Ч

    p=(pNode)malloc(sizeof(Node));

    p->data=x;

    //�Ȱ�������ڵ��ʡ����ʱ��������

    p->prior=q;
    p->next=q->next;

    q->next->prior=p;

    q->netx=p;
}


void Delete(PNode first,int i,DataType x)
{


    //pΪ����ָ��

    temp=q;//�ݴ�q

    q->prior->next=q->next;
    q->next->prior=q->prior;

    free(temp);
}





























