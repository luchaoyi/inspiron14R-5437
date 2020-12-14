/*************************************************************************
    > File Name: Btree.c
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年01月31日 星期六 19时40分55秒
    > Update Time: 2015年01月31日 星期六 19时40分55秒
 ************************************************************************/

#include<stdio.h>

struct 
{
	Key key;
	union {
		link next;  //B tree 内部节点是链接
		Item item; //B tree 外部节点是记录
	}ref;
}entry;

typedef struct Bnode{
	entry b[M];
	int m; //计数
}*link;

static int H;//Height
static int N;//Number

link NEW()
{
	link x = malloc(sizeof *x);
	x->m = 0;
	return x;
}

void BTinit()
{
	head = NEW();
	H=0;
	N=0;
}

Item searchR(link h,Key v,int H)
{
	int j;

	if(H==0)
		for(j=0;j<h->m;j++)
			if(eq(v,h->b[j].key))
				return h->b[j].Key
	else
	{
		for(j=0;j<h->M;j++)
		{
			if(j+1 == h->m) || less(v,h->b[j+1].key)
			{
				return searchR(h->b[j].ref.next,v,H-1)
			}
		}
	}

	return NullTime;
}



//插入时若节点溢出则分裂节点
//
link split(link h)
{
	int j;
	link t =NEW();

	for(j=0;j<M/2;j++)

		t->b[j] = h->b[M/2+j]; //挪动后一半
	h->m = M/2;
	t->m=h->M;

	return t;

}



link insertR(link h ,Item item,int H)
{
	if

	...
	
	if h->m <M return NULL;else return split(h);
}

//自顶向上可以在搜索时将满节点分裂
if STinsert(Item item)
{
	link t,u=insertR(head,item,H);


	if(u==NULL) return;

	t=NEW(); t->m=2;
	t->b[0].key = head->b[0].key;

	t->b[0].ref.next = head;
	t->b[1].Key = u->b[0].key;
	t->b[1].ref.next = u;
	head =t;
	H++;


}
