//��ʼ��ͷ��ʼ

quickPointer=head;

slowlPointer=head;

while(quickPointer!=NULL)//quickPointer��β
{
	slowlPointer=slowlPointer->next;

	quickPointer=quickPointer->next;
	
//�������ڵ�ʱquickPointer=quickPointer->next->next �൱�� NULL->next ��Ч����;
	if(quickPointer!=NULL)
		quickPointer=quickPointer->next;	
	
}
