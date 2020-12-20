#include<stdio.h>


typedef struct
{
    DataType data;
    BiNode *lChild,*rChild;
}BiNode,*pNode;


//ǰ�����
void PreOrder(pNode root)
{
    if(root==NULL)
        return;
    else
    {
        printf(root->data);/***�ȷ��ʸ��ڵ�***/
        PreOrder(root->lChild);//��
        PreOrder(root->rChild);//��
    }

}


void InOrder(pNode root)
{
    if(root==NULL)
        return;
    else
    {

        PreOrder(root->lChild);//��
        printf(root->data);/***���ʸ��ڵ�***/
        PreOrder(root->rChild);//��
    }


}

void PostOrder(pNode root)
{
     if(root==NULL)
        return;
    else
    {

        PreOrder(root->lChild);//��

        PreOrder(root->rChild);//��
        printf(root->data);/***���ʸ��ڵ�***/
    }

}

