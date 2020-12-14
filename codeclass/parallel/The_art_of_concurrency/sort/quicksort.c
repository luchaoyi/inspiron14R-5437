/*
此快排始终保持将大的换右,小的换左
不找中间元素
当i=j相遇时自然找到中间


 *3 4 2 1 9 6 8 5 10 7
 *^                  ^ 
 *i					 j					
*       ^
*		j 第一次迭代j停止位置 交换3,1
* 1 4 2 3 9 6 8 5 10 7
 *  i   j            r[i]>r[j] 交换
 *1 3 2 4 9 6 8 5 10 7
	i j                r[i]>r[j]
  1 2 3 4 9 6 8 5 10 7
	 i=j	
	 停止划分中间值自然为3


*3 4 2 1 9 6 8 5 10 7         若指定7为中值	<-i  7  j-> 因此i++ ,j--找到不符合关系的两个元素互换
 *i                j
 *    <7  i|    |j >7             交换9 和5         
 *3 4 2 1 5 6 8 9 10 7
			  i
			  j	                 停止交换8和7 

  3 4 2 1 5 6 |7| 9 10 8 
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



/*不使用递归的快排
 *
 * 使用栈或队列存储(lo,hi)对,启动多线程可以从中取出
 * 此快排启动多线程需要一个线程安全的stack or queue
*/

void QuickSort(){

	int first ,end ,mid;
	qSortIndex *d=NULL,*d1,*d2;

	//将(lo,hi)放在队列中，不使用递归,将划分后两段lo,hi存于任务队列，然后从队列中取出
	while(notEmpty(Q)){
		dequeue(Q,d);
		first=d->lo;
		end=d->hi;
		free(d);


		if(p<r)
			mid=Partition(A,first,end);
	//将两端加入队列  first  mid-1 |mid |mid +1  end
		d1=new qSortIndex;
		d1->lo=first;
		d1->hi=mid-1;
		enqueue(Q,d1);

		d2=new qSortIndex;
		d2->lo=mid+1;
		d2->hi=end-1;
		enqueue(Q,d2);

	}
}



//必须设置一个信号量来告诉其它线程，所有线程结束后才可以退出
void ParallelQuickSort(Q,A){

	nCores=num_get_num_procs();
	endFlag=nCores+1;

//初始时Q不应该为空，endFlag应该>=线程数最好
//无论endFlag为多少,最后队列为空时,endFlag不会被刷新,此时只执行endFlag-- ,最终使得endFlag<0会结束循环


#pragma omp parallel for 
	for(i=0;i<nCores;i++)
	{

	int first ,end ,mid;
	qSortIndex *d=NULL,*d1,*d2;

	while(endFlag>0)
	{
	//将(lo,hi)放在队列中，不使用递归,将划分后两段lo,hi存于任务队列，然后从队列中取出 


#pragma omp barrier 

#pragma omp atomatic
		{
			endFlag-=1;
		}

		
//放置barrier防止一个线程执行while(notEmpty(Q))里面代码时，Q为空，其它线程快速的执行endFlaf--
//即假设T0将endFlag置为5,而T1-T3执行了多次endFlag--,则endFlag会<0
//这个barrier相当于,在队列空时使线程等待

	while(notEmpty(Q)){
#pragma omp atomatic
		{
			endFlag=nCores+1;
		}

		dequeue(Q,d);
		first=d->lo;
		end=d->hi;
		free(d);

		if(p<r)
			mid=Partition(A,first,end);
	//将两端加入队列  first  mid-1 |mid |mid +1  end
		d1=new qSortIndex;
		d1->lo=first;
		d1->hi=mid-1;
		d2=new qSortIndex;
		d2->lo=mid+1;
		d2->hi=end-1;


#pragma omp critical
		{
			enqueue(Q,d1);
			enqueue(Q,d2);
		}
	}

	}

	}
}


