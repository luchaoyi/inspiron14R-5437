/*
各层互不影响;
//lgN记录了生成的新节点中最大层数 搜索插入节点位置时是从此层开始的
//跳跃表最高位lgN;
//使跳跃表中没t^j,个节点就有j+1个链接则j+1层链接可以跳过t^j个节点
//skip list 采用抛硬币的策略插入随机性的概率 1/2 1/4 1/8 。。。保证每层的平衡
*/
struct STnode* link;

struct STnode
{
	Item item;
	link *next;
	int sz; //层数
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
	
	//跳表搜索
	if(v <getkey(t->next[k]->item)); //若t->next[k]->item大表明跨度太大则下降一层
	{
		if(k==0) return NULLitem;
		
		return searchR(t,v,k-1);//递归搜索
		
	}
	
	//表明此最大跨度不足
	//由于此跨度要么是最大的要么是调整下来的
	//所以不是上升而是右移
	
		return searchR(t->next[k],v,k);//递归搜索
	
}	//v  == getkey(t->next[k]->item)

//lgN为层数
Item STsearch(Key v)
{
	return searchR(head,v,lgN);
}
int randX()
{
	//p(0-RAND_MAX) =1 以概率 1/2^j 概率 
	int i,j,t = rand();
	for (i=1,j=2; i<lgNMax;i++,j+=j)
		if(t> RAND_MAX/j) break;
	if(i>lgN) lgN=i; //lgN记录了生成的新节点中最大层数 搜索插入节点位置时是从此层开始的
	return i;
} 

insertR(link t,link x,int k);
{
	Key v = getkey(x->item);
	
	if(v <getkey(t->next[k]->item))//在 此范围中 
	{
		//k初始为lgN>=x->sz;
		if(k < x->sz)//当前层非 待插入的顶层 从上而下找位置各层互不影响
		{
			x->next[k] = t->next[k];
			t->next[k]=x;
		}
		if (k == 0) return ;
		
		insertR(t,x,k-1);//递归下层
		return ;
	}
	
	insertR(t->next[k],x,k);	
}

void STinsert(Item item)
{
	insertR(head,NEW(item,randX()),lgN);
	N++;
}

//删除跳跃表节点 
/*
	从上而下的断开链接
	直到底层
*/
void deleteR(link t,Key v,int k)
{
	link x = t->next[k];
	
	//删除存在的所以 会出现==getkey(x->item)
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
