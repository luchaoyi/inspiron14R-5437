

//����ɢ�к���
int Hash()
{

}

//������
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
	//else p=NULL û�ҵ��������������
	//ͬʱʵ�ֲ��ҺͲ������
	
	
	//û��βָ����������ȿ���ͷ�巨
	else
	{
		q=(Node*)malloc(sizeof(Node));
		q->data=k;
		
		q->next=ht[i];
		ht[i]=q;
	}
}