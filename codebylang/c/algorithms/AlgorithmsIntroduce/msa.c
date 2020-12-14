
/* 
 *最大子数组线性算法（编程珠玑）
 *
 * */

def msa(A):
	sum=0;
	maxSum=0;
	i=j=0;

	while j<A.len:
		sum+=A[j++];
		if sum>maxSum:
			maxSum=sum;
			start=i;
			end=j;
		//跨越负数区域代价太大则，放弃它
		if sum<0:
			sum=0;
			i=j;


/*  
分治法:
D:mid=(low+high)/2
C:递归
C:三种情况（start:end)左半,右半，跨越，取最大
*/


#define INF 无穷

//跨越部分@(n)
def find-max-cross(A,low,mid,high):
	left-sum=-INF
	sum=0
	for i=mid to low:
		sum+=A[i]
		if (sum>left-sum):
			left-sum=sum
			max-left=i;
	
	right-sum=-INF	
	sum=0
	for j=mid+1 to high:
		sum+=A[j]
		if(sum>right-sum):
			right-sum=sum
			max-right=j;
	return (max-left,max-right,left-sum+right-sum);

def find-max(A,low,high):
	//基本部分，不递归部分
	if(high==low):
		return (low,high,A[low]);
	else 
		mid=(mid+left)/2;
		(left-low,left-high,left-sum)=find-max(A,low,mid);
		(right-low,right-high,right-sum)=find-max(A,mid+1,high);
		(cross-left,cross-right,cross-sum)=find-max-cross(A,low,mid,high);
	//左，右，跨越进行比较
	index=maxIndex(left-sum,right-sum,cross-sum)
	switch index:
	{
		case 0:
			return (left-low,left-high,left-sum)
		case 1:
			return ...
		case 2:
			return ...
	}

//递归式复杂度分析
//1.猜测代入归纳 2.递归树 3.主定理
