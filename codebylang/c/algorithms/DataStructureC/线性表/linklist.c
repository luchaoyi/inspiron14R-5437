#include<stdio.h>


typedef struct LinkList
{
    DataType data;
    Node *next;
}Node,*pNode;


//��ʼ������ͷ�ڵ�
pNode InitList(pNode first)
{
    first = (pNode)malloc(sizeof(Node));
    first->next=NULL;
    //first->data=?//������ͷ�ڵ���������������

    return first;

}

//����
void PrintList(pNode first)
{
    pNode p =first->next; //��ʼָ���һ���ڵ�

    for(p;p->next!=NULL;p=p->next)
        printf(p->data);

        //count=1
        //count++
}


//ͷ�巨��������
pNode Create(pNode first,DataType a[],int n)
{
    pNode p;//һ������ָ��

    for()
    {
        p=(pNode)malloc(sizeof(Node));

        p->next= first->next;
        first->next=p;
    }
}

//β�巨��������
pNode Create(pNode first,DataType a[],int n)
{

        p
        q
        //����ָ��
    //p = malloc

    q->next->p
    p->next=NULL
    q=p;
}

//����ɾ��
pNode free()
{
    while(first->next!=NULL)
    {
        p=first->next;
        first->next=first->next->next;
        free(p);
    }
}


















