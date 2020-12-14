/*
	选择最小的元素和第一个元素交换
	选择次小的和第二个交换	
	//通过变量记录最小值下标
	//优化后的程序减少了交换次数
	
	//缺点对已有序序列依赖较少
*/
/*
void Sort(int a[],int n)
{
	int i,j;
	int temp;
	
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(a[j]<a[i])//从i后开始选择
			{
				temp=a[j];
				a[j]=a[i];
				a[i]=temp;
			}
			
		}
	}
	
}
*/
//通过变量记录最小值下标
//优化后的程序减少了交换次数
void SelectSort(int r[],n)
{
	
	for(i=0;i<n-1;i++)
	{   
		min=i;
		for(j=i+1;j<n;j++)
		{   
			if(r[j]<r[min])//选择最小的
			{
				min=j;
			}
		}
		//选择最小的放在最前面
		//优化后的程序减少了交换次数
		if(min!=i)
		{
			temp=r[min];
			r[min]=r[i];
			r[i]=temp;
		}
		
	}
}
