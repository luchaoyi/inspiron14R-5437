/*
	BST从根插入
	若new>root new-->root root作为左子树将root的右子树作为新根右子树
	然后进行旋转调整
	
	
	BST树每次的删除后调整树也是很浪费开销的所以可以考虑不动结构而是对
	删除节点标记为已删除
	
	//然后可以周期性的调整节约一些内存 折衷
*/


//BST右旋转

//循环是左子树作为根节点根转到x的右子树 x的原右子树
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
	首先将其插入到合适位置然后旋转时期成为主树的根节点
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


//增加计数域对select操作根有帮助
//不过对插入搜索操作有害
Item selectR(link h,k)
{
	if(h==z) return Nulltime
	
	t=h->l->N;
	
	if(t>k) //左子树节点树多于k个第k个在左边
		return selectR(h->l,k);
	if(t<k)
		return selectR(h->r,k-t-1);//左边不够，右边在补还需要k-t-1个
	//t==k
	return h->item;
		
}


//选择关键字大小排名为第k个的
Item STselect(int k)
{
		return selectR(head,k);
}

//划分树将第k个元素放在根然后旋转
link partR(link h,int k)
{
	int t = h->l->N;
	
	if(t>k)
	{
		//先找到第k个
		//然后要旋转
		//递归归去来袭
		//h=h->l一路递归下去返回是每步都要操作h
		//所以回来时继续用h->l;接受
		h->l=partR(h->l,k);
		
		h=rotR(h);
	}
	if(t<k)
	{
		h->r=partR(h->r,k-t-1);
		h=rotL(h);
	}
	
	//递归到最后
	return h;
}

//递归考虑v>t v<t 的搜索方式 处理留在v==t
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
	
	//删除就是找到点将此点 左右合并 然后释放此点
	
	{
		x=h;
		
		h=joinLR(h->l,h->r);
		
		free(x);
	}
	
	return h;
}

//要将 左右合并 然后释放此点
//由于原右边>左边 所以合并时对右边进行划分操作将最小元素带到树根
//此时右树根左边为空因为选择的是最小的作为根
//然后将左子树挂到右子树
link joinLR(link a,link,b)
{
	if(b==z) return a;
	
	b=partR(b,0);//将最小元素划到根
	//
	b->l=a;
	return b;
	
}
void STdelete(Key v);
{
	head = deleteR(head,v);
}

//两棵树的join操作
/*
	采用递归
	将一颗树以插入的手段与另一个合并
*/
link STjion(link a,link b)
{
	if(a==z) return b;
	if(b==z) return a;
	
	//选择a的根作为树根 根插入法插入到b
	b=insertT(b,a->item);
	
	//合并树
	
	b->l=STjoin(a->l,b->l);
	b->r=STjoin(a->r,b->r);
}






