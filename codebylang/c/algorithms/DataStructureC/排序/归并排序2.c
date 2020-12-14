

int MergeSort(int k[],int n)
{
	int i,left_min,left_max,right_min,right_max;
	
	int *temp =(int)malloc(n*sizeof(int));
	for(i=1;i<n;i*=2) //i*为步长；
	{
		//集合元素为1两个一组集合元素为2四个一组
		for(left_min=0;left_min<n-i;left_min=right_max)
		{
			//left_max与right_max刚好越界一个所以
			//循环后righ_min=left_max left_min=right_max
			left_max=left_min+i; 
			righ_min=left_max;
			right_max=right_min+i;
			//right_min=left_max=left_min+i;
			//right_max=left_max+i;
			if(right_max>n)
			{
				right_max=n;//越界矫正
			}
			int next=0; //temp
			while(left_min<left_max&&righ_min<right_max)
			{
				if(k[left_min]<k[right_min])
				{
					temp[next++] = k[left_min++] 
				}
				else
				{
					temp [next++] = k[righ_min++];
				}
				
				while(left_min<left_max)
				{
					k[--righ_min]= k[--left_min];
				}
				while(next>0)
				{
					k[--right_min]=temp[--next]; 
				}
			}
		}
	}
}