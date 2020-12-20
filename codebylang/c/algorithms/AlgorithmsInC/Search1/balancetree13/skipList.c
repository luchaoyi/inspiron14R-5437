/*
���㻥��Ӱ��;
//lgN��¼�����ɵ��½ڵ��������� ��������ڵ�λ��ʱ�ǴӴ˲㿪ʼ��
//��Ծ�����λlgN;
//ʹ��Ծ����ût^j,���ڵ����j+1��������j+1�����ӿ�������t^j���ڵ�
//skip list ������Ӳ�ҵĲ��Բ�������Եĸ��� 1/2 1/4 1/8 ��������֤ÿ���ƽ��
*/
struct STnode* link;

struct STnode
{
	Item item;
	link *next;
	int sz; //����
}

static link head,z;
static int N,int lgN;

link NEW(Item item,int k)
{
	int i;
	
	link x = malloc(sizeof *x);
	x->next=malloc(k*sizeof(link));
	
	x->item=item;
	x->sz= k;
	
	for(i=0;i<k;i++) x->next[i]=z;
	return x;

}
void STinit()
{
	N=0;lgN=0;
	z=NEW(NULLitem,0);
	
	head = NEW(NULLitem,lgNMax+1);
}

Item searchR(link t,Key v,int k)
{
	if(t==z) return NULLitem;
	
	if(v == getkey(t->item)) return t->item;
	
	//��������
	if(v <getkey(t->next[k]->item)); //��t->next[k]->item��������̫�����½�һ��
	{
		if(k==0) return NULLitem;
		
		return searchR(t,v,k-1);//�ݹ�����
		
	}
	
	//����������Ȳ���
	//���ڴ˿��Ҫô������Ҫô�ǵ���������
	//���Բ���������������
	
		return searchR(t->next[k],v,k);//�ݹ�����
	
}	//v  == getkey(t->next[k]->item)

//lgNΪ����
Item STsearch(Key v)
{
	return searchR(head,v,lgN);
}
int randX()
{
	//p(0-RAND_MAX) =1 �Ը��� 1/2^j ���� 
	int i,j,t = rand();
	for (i=1,j=2; i<lgNMax;i++,j+=j)
		if(t> RAND_MAX/j) break;
	if(i>lgN) lgN=i; //lgN��¼�����ɵ��½ڵ��������� ��������ڵ�λ��ʱ�ǴӴ˲㿪ʼ��
	return i;
} 

insertR(link t,link x,int k);
{
	Key v = getkey(x->item);
	
	if(v <getkey(t->next[k]->item))//�� �˷�Χ�� 
	{
		//k��ʼΪlgN>=x->sz;
		if(k < x->sz)//��ǰ��� ������Ķ��� ���϶�����λ�ø��㻥��Ӱ��
		{
			x->next[k] = t->next[k];
			t->next[k]=x;
		}
		if (k == 0) return ;
		
		insertR(t,x,k-1);//�ݹ��²�
		return ;
	}
	
	insertR(t->next[k],x,k);	
}

void STinsert(Item item)
{
	insertR(head,NEW(item,randX()),lgN);
	N++;
}

//ɾ����Ծ��ڵ� 
/*
	���϶��µĶϿ�����
	ֱ���ײ�
*/
void deleteR(link t,Key v,int k)
{
	link x = t->next[k];
	
	//ɾ�����ڵ����� �����==getkey(x->item)
	if(v<=getkey(x->item))
	{
		if(v==getkey(x->item))
			{
				t->next[k] = x->next[k];
			}
		if(k==0) free(x);
		
		deleteR(t,v,k-1);
	}
	
	deleteR(t->next[k],v,k);
	
}

void STdelete(Key v)
{
	deleteR(head,v,lgN);
	N--;
}
