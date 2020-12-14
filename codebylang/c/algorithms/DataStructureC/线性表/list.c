#include<stdio.h>

//顺序表
typedef struct List
{
    DataType    data[MAX_SIZE];
    int  ListLength;//长度
}List,*pList

void InitList(pList L)
{
    L->ListLength = 0;
}

//将数组元素输入List中
void CreateList(pList L,DataType a[],int n)
{
    int i;

    //判断输入合法？
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

//按位查找
DataType Get(pList L,int i)
{
    //判定i是否有效
    return L->data[i];
}

//按值查找
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

//插入
void Insert(pList L,int i,DataType x)
{
    //if判断有效
    int j;
    for(j=L->ListLength;j>=i;j--)
    {
        L->data[j]=L->data[j-1];
    }
    //元素后移
    L->data[i-1]=x;//赋值
    L.Length++;//元素个数增加
}

int  Delete(pList L, int i)
{

    x=L->data[i-1];

    for(int j=i-1;j<L->ListLength;j++)
    {
        L->data[j]=l->data[j+1];
    }
    //覆盖删除
    L->ListLength--;
    return x;
}

//判空

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














