/*
	�����˼�룺����������߿��Խ������������������������Ŀ�����
	�������в��ȶ����㷨����������Ǻ��б�Ҫ��
	
	
*/

/*
	���������Ҷ�ӽڵ������ڸ�����,���BST�����Խ��������д��ұ��⼫�����
*/
link insertR(link h,Item item)
{
	Key v=getkey(item), t = getkey(h->item); 
	
	if(h==z) return NEW(item,z,z,l);
	
	//�������
	if(rand<RAND_MAX/(h->N+1))
		return insertT(h,item);
	
	//*******************
	if(v<t) h->l = insertR(h->l,item);
	
	if(v>t) h->r = insertR(h->r,item);
	
	(h->N)++; return h;
	
	//*******************
}

void STinsert()
{
	head = insertR(head,item);
}





