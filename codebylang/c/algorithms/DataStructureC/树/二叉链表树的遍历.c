/x
���ڸ��ݶ������ı��������������
ǰ&��
��&��
˼·�Ǹ���ǰ��or������Ѱ�Ҹ�����������з֣��ݹ鹹����
ǰ:3 9 1 2 20 5 7
��:1 9 2 3 5 20 7
����ǰ�����3
	   |3|
(1 9 2)   (5 20 7)
(1 9 2) ǰ����9����ǰ������9
(5 20 7)ǰ����20����ǰ������20
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

