/*
	�ؼ����������� key-item;keyΪС�������� st[k]=item;
*/

struct Item
{
		int key;
		user_type data;
}

static Item *st;
static int M = maxKey;




Item STinit(int M)
{
	int i;
	
	st = malloc ((M+1)*sizeof(Item));
	
	for(i=0;i<=M;i++)
	{
		st[i]= NULLitem;

	}
	
	return st;
	
}

/*
	ɨ��ǿյ���Чitem
*/
int  STcount()
{
	int i,N=0;
	
	for(i=0;i<M;i++)
	{
		
		if(st[i] != NULLitem)
			N++;
	}
	
	return N;
}

void STinsert(Item item)
{
	st[getkey(item)]=Item;
}

Item STsearch(int k)
{
	return st[k];
}

//ɾ��һ��
void STdelete(Item item)
{
	st[getkey(item)] = NULLitem;
}

/*
	ѡ���num������ NULLitem��
*/
Item Select(int num)
{
	int i;
	
	for(i =0; i< M; i++)
	{
		if(st[i]!=NULLitem)
		{
			if(k-- == 0)		return st[i];
		}
	}
}
