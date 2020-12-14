/*
	二叉搜索树就是 左孩子<= 根 <=右孩子
	
	二叉搜索树中序遍历可以实现排序
	
	建立索引的思想
	对于数据项比较大的数据如：存储在外存大文件，可以建立索引，BST的item
	变为item的索引
*/

#include<stdlib.h>

static link head //指向根
static z//在为哑节点 当树空时head->z 构造虚拟节点可以使动作统一


struct STnode
{
	Item item;
	link r,l;
	int N; //存放每个节点链接的节点个数
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

//递归
int insertR(link h,Item item)
{
		if(h==z) return New(item,z,z,l); //哑节点使用的很妙
		
		else
		{
			k=getkey(Item); t=getkey(h->item）
			
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

//中根遍历实现排序
void sort(link h)
{
	if(h==z) return;
	sort(h->l);
	visit(h);
	sort(h->r);
}



