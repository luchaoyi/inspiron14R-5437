void InsertSort(L)
{

	for(i=2;i<=L.len;i++)
	{
		L.k[0]=L.k[i];

		//升序
		for(j=i-1;L.k[j]>L.k[0];j--)
		{
			L.k[j+1]=L.k[j];
		}

		L.k[j+1]=L.k[0];
	}
}
//优化排序思路：减少比较和移动

//折半插入排序，排序有序无序区  |有序区|无序区|在有序区搜寻插入位置
void BInsertSort(SqList &L)
{
	      
	for(i=2;i<=L.len;i++)
	{
		L.k[0]=L.k[i];

		//升序
		
		low=1;high=i-1;
		while(low<=high) //当low==high时还要循环最后一次，最后一次.插入位置为high+1
		{
			m=(low+high)/2;
			if(L.k[m]<l.k[0]) high=m-1;   
			else low = m+1;
		}

		for(j=i-1;j>=high+1;j--)
		{
			L[j+1]=L[j];
		}

		L.k[high+1]=L.k[0];
	}
}




//交换排序
//冒泡排序
void BubbleSort(L)
{
	
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(L[j]<L[j-1])
			{
				exch(L[j],L[j-1]);
			}
		}
	}

}


//二分
void QuickSort(L,low,high)
{
	mid=Partion(L,low,high);


	QuickSort(L,low,mid-1);
	QuickSort(L,L,mid+1,high);
}



int Partition(L,int first,int end)
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

//定位后在交换,优化的冒泡,减少冒泡交换
void SelectSort(L)
{
	//L[0] 未用辅助空间
	
	for(j=1;j<=n;j++)
	{
		L[0]=L[j];
		i=j;
		for(k=j+1;k<=n;k++)
		{
			if(L[k]<L[0])
			{
				i=k;
				L[0]=L[k];
			}
		}
		//exch(i,j)
		L[0]=L[j];
		L[j]=L[i];
		L[i]=L[0];

	}
}


//两路插入排序 d同样大小数组辅助 用某值将原数组划分为小于此和大于此，填入d中在整理
//而不在原数组交换，挪动
Tow_InsertSort(L)
{
	first=1;
	end=n-1;

	d[0]=L[0];
//	|first -->        L[1]<*|*>L[1]               <--end|
	for(i=1;i<n;i++)
	{
		if(L[i]>L[0]) InsertSort(L,1,i);
		else InsertSort(L,end,n-1);
	}
}




//归并:分治
MergeSort(L,low,high)
{
	if(low<high)
	{

	mid=(low+high)/2;
	MergeSort(L,low,mid);
	MergeSort(L,mid+1;high);
	Merge(L,low,high); 
	}
}



//Adjust i L end n 
HeapAdjustToptodown(L,i,n)
{
	//小顶堆
	while(j<=n)
	{
		j=2*i;
		//j=n ++就越界了
		if(j<n&&L[j]>L[j+1]) j++;//i指向更小的
		if(L[j]>L[i]) break;//位置好着 

		exch(L[j],L[i]);
		i=j;
	}
}

HeapSort(H)
{
	for(i=H.len/2;i>1;i--)
		HeapAdjustToptodown(H,i,H.len);
	for(i=H.len;i>1;i--)
	{

		exch(H[1],H[i]); //最大元素换到结尾
		HeapAdjustToptodown(H,1,i-1);
	}
}


//基数排序：是一种多关键字排序，依次比较主次关键字
//LSD:从低位到高位，先比较低优先级关键字，则后面的高优先级比较可以否决前面低优先级所以变动范围是全局的.
//MSD：由高到低，
//先比较优先，所以后面的比较是局部微调是分层次，分级的比较树型的



#define MAX_NUM_OF_KEY 8
#define RADIX 10
#define MAX_SPACE 10000

//静态链表
typedef struct{
	KeyType keys[MAX_SPACE];
	InfoType otheritems;
	int next;
}

//静态节点用r0将未分配的节点串起来，分配时
typedef struct{
	SLCell r[MAX_SPACE]; //r0为头节点
	int keynum; //关键字个数
	int recnum;  //当前长度
}SLList;

typedef int Arrtype[RADIX];



//按key[i]分发到子表  f-->frist e-->end
void Distribute(SLCell &r,int i,Arrtype &f,Arrtype &e)
{
	//r是原始数据链表
	// 0-->-->...-->0
	for(j=0;j<RADIX;++j) f[j]=0;
	for(p=r[0].next;p;p=r[p].next)
	{
		//p号元素链接到f[j]
		j=ord(r[p].keys[i]);
		if(!f(j)) f[j]=p;
		//从尾部插入 r[e[j]].next e[j]-->元素为j容器尾直接在尾部插入 r[e[j]].next=p;
		else r[e[j]].next = p;
		e[j]=p; 
	}
}


//将两个链表合并为一个时，有尾指针时合并非常方便
void Collect(SLCell &r,int i ,Arrtype f,Arrtype e)
{
	for(j=0;!f[j];j++); //求第一个非空子表
	r[0].next=f[j]; t=e[j];
	while(j<RADIX)
	{
		//找下一个非空子表，将连个链接在一起，前未指向后面的头
		for(++j;j<RADIX-1&&!f[j];j++);
		if(f[j]) { r[t].next=f[j];t=e[j];}
	}
	r[t].next=0; //结尾
}


void RADIXSort(SLList &L)
{
	for(i=0;i<keynum;++i) L.r[i].next=i+1; //初始化
	L.r[L.recnum].next = 0 ; //结尾-->0

	for(i=0;i<L.keynum;+++i)
	{
		Distribute(L.r,i,f,e);
		Collect(L.r,i,f,e);
	}

}




