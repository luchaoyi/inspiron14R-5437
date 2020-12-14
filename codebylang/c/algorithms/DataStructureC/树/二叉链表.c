#include<stdio.h>


typedef struct
{
    DataType data;
    BiNode *lChild,*rChild;
}BiNode,*pNode;


//前序遍历
void PreOrder(pNode root)
{
    if(root==NULL)
        return;
    else
    {
        printf(root->data);/***先访问根节点***/
        PreOrder(root->lChild);//左
        PreOrder(root->rChild);//右
    }

}


void InOrder(pNode root)
{
    if(root==NULL)
        return;
    else
    {

        PreOrder(root->lChild);//左
        printf(root->data);/***访问根节点***/
        PreOrder(root->rChild);//右
    }


}

void PostOrder(pNode root)
{
     if(root==NULL)
        return;
    else
    {

        PreOrder(root->lChild);//左

        PreOrder(root->rChild);//右
        printf(root->data);/***访问根节点***/
    }

}

