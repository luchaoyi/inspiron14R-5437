//Shaker排序是双向冒泡排序
//从前向后，记录最后发生交换的位置
//从后向前时从最后发送交换记录位置进行

sort(a,len){
	int i.left=0,right=len-1;shift=0;

	while(left<right){
		for(i=left,i<right;i++){
			if(a[i]>a[i+1]){
				swap(a,i.i+1);
				shift=i; //记录发送交换位置
			}

		}

		right=shift;//从最后发生交换位置开始
		for(i=right;i>left;i--){
			if(a[i]<a[i-1])
			{
				swap(a,i.i-1);
				shift=i; //记录发送交换位置
			}
		
		}

		left=shift;
	}
}
