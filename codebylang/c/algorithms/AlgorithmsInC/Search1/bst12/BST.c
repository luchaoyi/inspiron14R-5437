/*
	�������������� ����<= �� <=�Һ���
	
	���������������������ʵ������
	
	����������˼��
	����������Ƚϴ�������磺�洢�������ļ������Խ���������BST��item
	��Ϊitem������
*/

#include<stdlib.h>

static link head //ָ���
static z//��Ϊ�ƽڵ� ������ʱhead->z ��������ڵ����ʹ����ͳһ


struct STnode
{
	Item item;
	link r,l;
	int N; //���ÿ���ڵ����ӵĽڵ����
} *link;

link New(Item item,link r,link l,int N)
{
	link x=malloc(sizeof(STnode));
	
	x->item=item;
	x->r=r;
	x->l=l;
	x->N=N;	
}

void init()
{
	head = New(Nullitem,NULL,NULL,0);
}



void STinsert(Item item)
{
	head= insertR(head,item);
}

//�ݹ�
int insertR(link h,Item item)
{
		if(h==z) return New(item,z,z,l); //�ƽڵ�ʹ�õĺ���
		
		else
		{
			k=getkey(Item); t=getkey(h->item��
			
			if(k>=t) //right
			{
				insertR(h->r,item);
			}
			else
			{
				insertR(h->l,item);
			}
		}
		
			h->N++;
			return h;
}

int STcount()
{
	return head->N;
}


Item STsearch(Key v)
{
	return searchR(v);
}

Item searchR(link h,Key v)
{
		Key t= getkey(h->item);
		
		if(h==z) return Nullitem;// not found
		
		else 
		{
			if(t==v)
				return (h->item);
			if(t>v)
				return searchR(h->l,v);
			else
				return searchR(h->r,v);
		}
			
		
	
}

//�и�����ʵ������
void sort(link h)
{
	if(h==z) return;
	sort(h->l);
	visit(h);
	sort(h->r);
}



