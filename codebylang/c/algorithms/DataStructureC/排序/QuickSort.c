/*
此快排始终保持将大的换右,小的换左
不找中间元素
当i=j相遇时自然找到中间*/

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
