#include<stdio.h>


typedef struct LinkList
{
    DataType data;
    Node *next;
}Node,*pNode;


//初始化生成头节点
pNode InitList(pNode first)
{
    first = (pNode)malloc(sizeof(Node));
    first->next=NULL;
    //first->data=?//可以在头节点数据域存放链表长度

    return first;

}

//遍历
void PrintList(pNode first)
{
    pNode p =first->next; //开始指向第一个节点

    for(p;p->next!=NULL;p=p->next)
        printf(p->data);

        //count=1
        //count++
}


//头插法建立链表
pNode Create(pNode first,DataType a[],int n)
{
    pNode p;//一个申请指针

    for()
    {
        p=(pNode)malloc(sizeof(Node));

        p->next= first->next;
        first->next=p;
    }
}

//尾插法建立链表
pNode Create(pNode first,DataType a[],int n)
{

        p
        q
        //两个指针
    //p = malloc

    q->next->p
    p->next=NULL
    q=p;
}

//整表删除
pNode free()
{
    while(first->next!=NULL)
    {
        p=first->next;
        first->next=first->next->next;
        free(p);
    }
}


















