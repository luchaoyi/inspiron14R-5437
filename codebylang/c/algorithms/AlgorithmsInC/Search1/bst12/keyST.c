/*
	关键字索引搜索 key-item;key为小整数所以 st[k]=item;
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
	扫描非空的有效item
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

//删除一个
void STdelete(Item item)
{
	st[getkey(item)] = NULLitem;
}

/*
	选择第num个跳过 NULLitem的
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
