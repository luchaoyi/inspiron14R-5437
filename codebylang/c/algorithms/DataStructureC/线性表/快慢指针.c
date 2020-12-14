//初始从头开始

quickPointer=head;

slowlPointer=head;

while(quickPointer!=NULL)//quickPointer到尾
{
	slowlPointer=slowlPointer->next;

	quickPointer=quickPointer->next;
	
//奇数个节点时quickPointer=quickPointer->next->next 相当于 NULL->next 无效引用;
	if(quickPointer!=NULL)
		quickPointer=quickPointer->next;	
	
}
