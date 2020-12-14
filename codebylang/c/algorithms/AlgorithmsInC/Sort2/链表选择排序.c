#include<stdio.h>




struct deresult 
{
	int count;
	char symbol[10];
	deresult *next;
}

//综合考虑各种排序算法，感觉都不适合优化链表
//考虑用选择排序,算法复杂度O(n^2);
deresult *link_sort(deresult *h)
{
	deresult *p;//工作指针
	deresult *min;//min指针next记录最小值
	
	deresult *q; //工作指针
	deresult *r;//返回指针
	
	r=(deresult *)malloc(sizeof(deresult));//接受链表构造一个头
	
	q=(deresult *)malloc(sizeof(deresult));//插入一个头可以减少判断
	q->next=h;
	h=q;
	
	q=r;
	
		
	while(h->next!=NULL)
	{
		for(p=h->next,min=h;p->next!=NULL;p=p->next)
		{
			if((p->next->count)<(min->next->count))
			{
				min=p;
			}
		}
			q->next=min->next;
			min->next=min->next->next;
			q=q->next;
	}
	
	//将r头删掉
	q=r;
	r=r->next;
	free(q);
	free(h);
	
	return r;
}
