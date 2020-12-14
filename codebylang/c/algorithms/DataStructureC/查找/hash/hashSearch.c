

//构造散列函数
int Hash()
{

}

//拉链法
Node *HashSearch(Node *ht[],int m,int k)
{
	i=Hash(k);
	p=ht[i];
	while((p!=NULL)&&p->data!=k)
	{
		p=p->next;
	}
	if(p->data==k)
		return p;
	//else p=NULL 没找到，不存在则插入
	//同时实现查找和插入操作
	
	
	//没有尾指针情况下优先考虑头插法
	else
	{
		q=(Node*)malloc(sizeof(Node));
		q->data=k;
		
		q->next=ht[i];
		ht[i]=q;
	}
}