
/*
	大顶堆：根节点大
	小顶堆：根节点小
*/
/*
	堆中每一个节点的父节点为[k/2]（c默认向下取整）
	子节点 2K 2K+1
*/

/*	
	自顶下向下
	
	尧舜时代的k节点
	
	相当于k身居高位 三省吾身
	
	看看这否有比自己有能力的下属
	有则禅让位与下	
		exch(a[k],a[i]);
		k=i;
	
	没有则安心工作
	if(!less(a[k],a[i])) break;
	而且这一让根本停不下来说不定就到底了while(i<=N)
	
*/
void fixdown(int a[],int k,int n)
{
	
	
	while(i<=N)
	{
		i=2*k;
		
		if(!less(a[i],a[i+1])) i++ //换到a[i]
		if(!less(a[k],a[i])) break;
		
		exch(a[k],a[i]);
		k=i;
	}
}

/*
	自底向上：修正的是父节点
	
	进击的k节点：
	
	相当于k节点从基层做起然后野心勃勃要升职
	
	k试探能否拉自己的老板下马less(a[k],a[k/2]
	
	如果可以则拉下马
	exch(a[k],a[k/2]);
	k=k/2;
	直到找到比自己牛逼的老板
	才安心工作
	
	或到最高位停止(k<1)
*/


void  fixup(int a[],int k)
{
	while(k>1&&less(a[k],a[k/2])) //子比父小 //考量自己是更有优势
	{
		exch(a[k],a[k/2]);
		k=k/2;
	}
}


//-----------------------------------------------
/*
	思想减小：
	先构造堆
	然后将最大元素放到尾然后缩小待排序空间
*/
void heapsort(int a[],int l,int r)
{
	
	N=r-l+1;
	int *p=a+l-1;
	//键堆
	for(k=N/2;k>l;k--)
		fixdown(p,k,N);
	
	//排序
	while(N>1)
	{	
		exch(a[1],a[N]);
		fixdown(p,1,--N);	
	}
	
}	
