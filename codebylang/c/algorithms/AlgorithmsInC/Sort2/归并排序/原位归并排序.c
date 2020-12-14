/*

	核心思想：归并时将一半正序复制一半倒序复制
	然后指针左右移动类似快速排序的方式将其写回到a数组
	
*/
int aux[MAX]
void merge(int a[],int l,int m,int r)
{
	for(i=m+1;i>l;i--) aux[i-1]=a[i-1];
	for(j=m;j<r;j++)	aux[r+m-j]=a[j+1];
	//i j指针运动到了两头
	for(k=l;k<r;k++)
		if(less(aux[i],aux[j]))
			a[k]=aux[i++];
		else
			a[k]=aux[j++];
	
}

//自顶向下归并0
void mergesort(int a[],int l, int r)
{
	int m=(r+l)/2;
	
	if(r<=l) return;
	
	mergesort(a,l,m);
	mergesort(a,m+1,r);
	
	merge(a,l,m,r);

}

//自底向上
//核心思想：归并从下开始两个一组-->4--->8

void mergesort(int a[],int l, int r)
{
	for(m=1;m<=r-l;m=m+m)
	{
		for(i=l;i<r;i+=m)
		{
			merge(a,i,i+m-1,min(i+m+m-1,r));
		}
		
	}
}

