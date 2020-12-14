#define MAXSIZE 1000

typedef struct {
	ElemType data;
	int cur;
}component,SLinkList[MAXSIZE];

//像操作链表指针一样操作cur

int LocateElment_SL(SLinkList S,ElemType)
{
	//返回 index
	//S[0] 头节点位置
	i=S[0].cur;

	//末尾元素cur=0
	while(i&&S[i].data!=e) i=S[i].cur;
	
	return i;
}

//将所有未用的空间和删除出的空间链在一起形成一个链边，插入时从此链表取得一个元素
//备用链表以space[0].cur为头指针

void InitSpace_SL(SLinkList &space)
{
	for(i=0;i<MAXSIZE-1;i++) space[i].cur=i+1;
	space[0].cur=0;//都未用
}


//静态链表用malloc和free管理有效利用空间
int Malloc_SL(SLinkList &space)
{
	i=space[0].cur;

	//链表非空,没有指向自己
	if(space[0].cur) space[0].cur=space[i].cur; 

	return i;
}

//将k下标元素收回
void Free_SL(SLinkList &space,int k)
{
	space[k].cur=space[0].cur;
	space[0].cur=k;

}

//用以上三个函数作为基础可以实现像链表一样管理静态链表

void diffrence(SLinkList &space,int &S)
{
	InitSpace_SL(space);
	S=Malloc_SL(space);
	r=S;

	//A,B元素个数
	scanf(m,n);

	//建立A集合S
	for(i=0;i<m;i++)
	{
		space[r].cur=Malloc_SL(space);
		scanf(space[r].data);
		r=space[r].cur;
	}
	space[r].cur=0;//末尾置空

	//A-B U B-A == A u B-A n B;
	for(i=0;i<n;i++)
	{
		scanf(b);

		p=S;k=space[S].cur;

		while(k!=space[r].cur&&space[k].data!=b)
		{
			p=k;	
			k=space[k].cur;
		}

		// if not found append rear
		if(k==space[r].cur) {
			space[r].cur=Malloc_SL(space);
			scanf(space[r].data);
			r=space[r].cur;

		}
		//if find from S delete element
		else
		{
			space[p].cur=space[k].cur;
			Free_SL(space,k);

			//若删了尾节点 r需改动
			if(r==k) r=p;
		}

	}
}


