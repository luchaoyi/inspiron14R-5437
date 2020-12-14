

link reverse(link x)
{
	link t;y=x;r=NULL;
	
	while(y!=NULL)
	{
		t=y->next;
		
		y->next=r;//y当前处理节点 转向到前一个节点
		
		r=y;
		y=t;
		
	}
	
	return r;	
}
