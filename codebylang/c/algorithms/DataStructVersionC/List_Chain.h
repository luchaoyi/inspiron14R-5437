//#########################//

typedef struct LNode{

	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

Status GetElem_L(LinkList L,int i,ElemType &e)
{
	//寻找第i个顺序查找 需设置一个计数的
	p=L->next;//带头
	j=1;

	while(j<i&&p) 
	{
	 p=p->next;
	 ++j;
	}

	if(!p || j>i) return ERROR;

	e=p->data;

	return OK;

}

Status ListInsert_L(LinkList &L,int i,ElemType e)
{
	//第i个元素之前插入,带头的。指向第i-1个指针
	
	LinkList p=L->next;
	j=1;

	LinkList q = (LinkList)malloc(sizeof(LNode));
	if(!q) return OVERFLOW;

	q->data=e;

	while(j<i-1&&p->next)
	{
		p=p->next;
		++j;
	}
	
	if(!p->next || j>i-1) return ERROR; //插到不存在元素之前

	q->next=p->next;
	p->next=q;

	return OK;
}


//删除和插入一下需找到前一个元素
Status ListDelete_L(LinkList &L)
{
	//第i个元素之前插入,带头的。指向第i-1个指针
	
	LinkList p=L->next;
	LinkList q;
	j=1;


	while(j<i-1&&p->next)
	{
		p=p->next;
		++j;
	}
	
	if(!p->next || j>i-1) return ERROR; 

	q=p->next;
	p->next=p->next->next;

	free(q);

	return OK;
}

//建立链表有插入到尾和头两种
void CreateList_L(LinkList &L,int n)
{
	L=(LinkList)malloc(sizeof(LNode)); //头节点

	for(i=n;i>0;--i)
	{
		p=(LinkList)malloc(sizeof(LNode)); 
		scanf(&p->data);

		p->next=L->next;
		L->next=p;
		
	}
}

void MergeList(LinkList &La,LinkList &Lb LinkList &Lc)
{
	pa=LinkList->next;
	pb=LinkList->next;

	pc=Lc=La; //需要一个头节点用La的不在申请了

	while(pa&&pb)
	{
		if(pa->data>pb->data)
		{
			pc->next=pa;
			pa=pa->next;

			pc=pc->next;
			//pc->next=NULL;

		}
		else
		{
			pc->next=pb;
			pb=pb->next;

			pc=pc->next;
			//pc->next=NULL;
		}

	}

	//剩余段
	pc->next= pa?pa:pb;
	free(Lb);

}

















