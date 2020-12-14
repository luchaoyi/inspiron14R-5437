Item max(Item a[],int left,int right)//max作用就是求最大值
{
	Item l,r; m=(left+right)/2;
	if(left=right) //1.考虑递归终止条件;2.考虑是头递归还是尾递归
		return a[left];//a[left]=a[right]
	//无终止则递归
	
	l=max(a,left,m);
	r=max(a,m+1,right);
	
	if(l>r) return l;
	else return r;
}
