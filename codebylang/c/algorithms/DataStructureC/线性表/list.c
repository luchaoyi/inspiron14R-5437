#include<stdio.h>

//˳���
typedef struct List
{
    DataType    data[MAX_SIZE];
    int  ListLength;//����
}List,*pList

void InitList(pList L)
{
    L->ListLength = 0;
}

//������Ԫ������List��
void CreateList(pList L,DataType a[],int n)
{
    int i;

    //�ж�����Ϸ���
    if(n>MAX_SIZE)
        printf("error!");

    for(i=0;i<=n;i++)
    {
        L->data[i]=a[i];

    }
    L->ListLength = n;
}

int LengthOfList(pList L)
{
    return L->ListLength;
}

//��λ����
DataType Get(pList L,int i)
{
    //�ж�i�Ƿ���Ч
    return L->data[i];
}

//��ֵ����
int Locate(pList,DataType x)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(L->data[i]==x)
            return i;
            //return i+1
    }
}

//����
void Insert(pList L,int i,DataType x)
{
    //if�ж���Ч
    int j;
    for(j=L->ListLength;j>=i;j--)
    {
        L->data[j]=L->data[j-1];
    }
    //Ԫ�غ���
    L->data[i-1]=x;//��ֵ
    L.Length++;//Ԫ�ظ�������
}

int  Delete(pList L, int i)
{

    x=L->data[i-1];

    for(int j=i-1;j<L->ListLength;j++)
    {
        L->data[j]=l->data[j+1];
    }
    //����ɾ��
    L->ListLength--;
    return x;
}

//�п�

bool Empty(pList L)
{
    if(L->ListLength == 0)
        return true;
    else
        return false;
}

void PrintList(pList L)
{
    for(i=0;i<L->ListLength;i++)
        printf(L->data[i]);

}














