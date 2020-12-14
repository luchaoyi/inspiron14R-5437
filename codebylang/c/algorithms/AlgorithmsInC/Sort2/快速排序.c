
/*
	通过划分来排序
	核心在划分中排序
	
	在找到位置i使
	
	a[l]->a[i-1]<a[i]<a[i+1]->a[r]
	
	改进：1 使划分元素尽可能的位于中间使用 多者取中a[l],a[r],a[mid],[a[randindex]]
		  2 改进递归最小颗粒度
*/

int partition(a,l,r)
{
	int temp=a[l];
	int i=l;
	int j=r;
	//中间划分元素随便选定暂存
	//
		while(i<j)
		{
			while(a[i]<temp])
				i++;
			while(a[j]>temp)
				j--;
			exchange(a[i],a[j]);
		}
		
		a[l]=a[i]
		a[i]=temp;
		return i;
}

void QuickSort(int a[],l,r)
{
	if(l>=r)
		return;
	//改进
	/*
		if(r-l<M)
			insertsort(a,l,r);
	*/
	i=partition(a,l,r);//关键在于划分在划分中排序
	
	quicksort(a,l,i-1);
	quicksort(a,i+1,r);
}

/*
	
	观察到递归只是传参核心是划分
	
*/




/*
不选主元的划分
此快排始终保持将大的换右小的换左
不找中间元素
当i=j相遇时自然找到中间
*/
int Partition(int r[],int first,int end)
{
	int i=first,j=end;
	int temp;
	while(i<j)
	{
		//左右交换走
		//升序
		
		while(i<j&&r[i]<=r[j]) //右
			j--;
		//结束循环时遇到了r[i]>r[j]交换
		if(i<j)
		{
			temp =r[i];
			r[j]=r[i];
			r[i]=temp;
			i++;
		}
		while(i<j&&r[i]<=r[j])//左
			i++;
		//结束循环时遇到了r[i]>r[j]交换
		if(i<j)
		{
			temp =r[i];
			r[j]=r[i];
			r[i]=temp;
			j--;
		}
	}
	return i;
}


void QuickSort(int r[],int first,int end)
{
	if(first<end)
	{
		pivot=Partition(r,first,end);//划分
		QuickSort(r,first,pivot-1);//左
		QuickSort(r,pivot+1,end);//右
	}
}





/*
 *三路切分快排
 *
 * */


//l   <v lt    ==v    gt >v   r

void sort(int* a,int l, int r)
{
	if(r<=l) return ;

	int lt=l,gt=r;
	int i=l+1;
	
	int v = a[l];

	while(i<=gt)
	{
		if(a[i]<v)
		{
			exchange(a[i++],a[lt++]);
		}
		else if(a[i]>v)
		{
		//这里的i不动,因为gt换到i位置，gt是未判定元素
			exchange(a[i],a[gt--]);
		}
		else
			i++
	}
//三路切分快排考虑了==v情况，在存在大量重复元素时速度有明显提升.
	//a[l...lt-1]<v | a[lt...gt]==v|a[gt+1...r]>v
	sort(a,l,lt-1);
	sort(a,gt+1,r);

}









