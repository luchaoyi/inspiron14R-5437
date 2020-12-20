/*
	BST�Ӹ�����
	��new>root new-->root root��Ϊ��������root����������Ϊ�¸�������
	Ȼ�������ת����
	
	
	BST��ÿ�ε�ɾ���������Ҳ�Ǻ��˷ѿ��������Կ��Կ��ǲ����ṹ���Ƕ�
	ɾ���ڵ���Ϊ��ɾ��
	
	//Ȼ����������Եĵ�����ԼһЩ�ڴ� ����
*/


//BST����ת

//ѭ������������Ϊ���ڵ��ת��x�������� x��ԭ������
link rotR(link h)
{
	link x=h->l;
	h->l = x->r;
	x->r=h;
	
	return x;
}

link rotL(link h )
{
	link x=h->r;
	
	h->r=x->l;
	
	x->l=h;
}



/*
	���Ƚ�����뵽����λ��Ȼ����תʱ�ڳ�Ϊ�����ĸ��ڵ�
*/
link insertT(link h,Item item)
{
	Key v = getkey(item);
	
rf	if(h==z) return NEW(item,z,z,l); 
	
	
	if(v>getkey(h->item))
	{
		h->l =insertT(h->l,item); 
		
		
		rotR(h);
	}
	else
	{
		h->r = insertT(h->r,item);
		
		rotL(h);
	}
	
	return h;
}


void STinsert(Item item)
{
	head = insertT(head,item);
}


//���Ӽ������select�������а���
//�����Բ������������к�
Item selectR(link h,k)
{
	if(h==z) return Nulltime
	
	t=h->l->N;
	
	if(t>k) //�������ڵ�������k����k�������
		return selectR(h->l,k);
	if(t<k)
		return selectR(h->r,k-t-1);//��߲������ұ��ڲ�����Ҫk-t-1��
	//t==k
	return h->item;
		
}


//ѡ��ؼ��ִ�С����Ϊ��k����
Item STselect(int k)
{
		return selectR(head,k);
}

//����������k��Ԫ�ط��ڸ�Ȼ����ת
link partR(link h,int k)
{
	int t = h->l->N;
	
	if(t>k)
	{
		//���ҵ���k��
		//Ȼ��Ҫ��ת
		//�ݹ��ȥ��Ϯ
		//h=h->lһ·�ݹ���ȥ������ÿ����Ҫ����h
		//���Ի���ʱ������h->l;����
		h->l=partR(h->l,k);
		
		h=rotR(h);
	}
	if(t<k)
	{
		h->r=partR(h->r,k-t-1);
		h=rotL(h);
	}
	
	//�ݹ鵽���
	return h;
}

//�ݹ鿼��v>t v<t ��������ʽ ��������v==t
link deleteR(link h,Key v)
{
	link x; Key t =getkey(h->item);
		
	if(h==z) return z;
	
	
	if(v>t)
	{
		h->r=deleteR(h->r,v);
	}
	
	if(v<t)
	{
		h->l=deleteR(h->l,v);
	}
	
	//v==t
	
	//ɾ�������ҵ��㽫�˵� ���Һϲ� Ȼ���ͷŴ˵�
	
	{
		x=h;
		
		h=joinLR(h->l,h->r);
		
		free(x);
	}
	
	return h;
}

//Ҫ�� ���Һϲ� Ȼ���ͷŴ˵�
//����ԭ�ұ�>��� ���Ժϲ�ʱ���ұ߽��л��ֲ�������СԪ�ش�������
//��ʱ���������Ϊ����Ϊѡ�������С����Ϊ��
//Ȼ���������ҵ�������
link joinLR(link a,link,b)
{
	if(b==z) return a;
	
	b=partR(b,0);//����СԪ�ػ�����
	//
	b->l=a;
	return b;
	
}
void STdelete(Key v);
{
	head = deleteR(head,v);
}

//��������join����
/*
	���õݹ�
	��һ�����Բ�����ֶ�����һ���ϲ�
*/
link STjion(link a,link b)
{
	if(a==z) return b;
	if(b==z) return a;
	
	//ѡ��a�ĸ���Ϊ���� �����뷨���뵽b
	b=insertT(b,a->item);
	
	//�ϲ���
	
	b->l=STjoin(a->l,b->l);
	b->r=STjoin(a->r,b->r);
}






