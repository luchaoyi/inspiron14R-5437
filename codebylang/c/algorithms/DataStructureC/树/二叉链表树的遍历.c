/x
关于根据二叉树的遍历来构造二叉树
前&中
后&中
思路是根据前序or后序来寻找根将中序遍历切分，递归构建树
前:3 9 1 2 20 5 7
中:1 9 2 3 5 20 7
根据前序根是3
	   |3|
(1 9 2)   (5 20 7)
(1 9 2) 前序中9在最前，根是9
(5 20 7)前序中20在最前，根是20
=>
   3
 9   20
1 2 5  7
x/










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

