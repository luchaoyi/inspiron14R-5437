/*************************************************************************
    > File Name: 2.4.2.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月30日 星期六 17时42分12秒
    > Update Time: 2015年05月30日 星期六 17时42分12秒
 ************************************************************************/

#include<iostream>
using namespace std;

//堆：小顶or大顶 根小于或大于孩子
//插入到末尾然后向上提升直到符合堆要求
//删除时去掉根节点将最最后一个节点换到根向下交换
//
//

//左孩子编号: *×2+1 
//右孩子:     *×2+2
//父节点编号则为 (* -1)/2
int heap[MAX_N],sz=0;

push(int x)
{
	//x节点编号 sz指示末尾空位置
	int i = sz++;

	heap[i]=x;
	while(i > 0 )
	{
		p=(i-1)/2;

		if(heap[p]>heap[i])
		{
				swap(heap,p,i);
				i=p;
	    }
		else
			break;
	}

}

int pop()
{
	int x= heap[0];

	heap[0]= heap[sz--];

	int i = 0;
	//下探
	while(i<sz)
	{
		s1=i*2+1;
		s2=i*2+2;


		//优化不使用Si
		Si=minindex(heap,S1,S2);

		//s1=minindex(heap,s1,s2);
          
		if(heap[i] > heap[Si])
		{

			swap(heap,Si,i);

		}
		return x;
		else
			break;

	}

	return x; 
}

//
//加油问题 
//若通过加油站则认为获得了加油机会将此加油站加油量加入优先队列，有种打游戏的感觉
//若最少次数加油则，每次油量为0时从优先队列取出元素认为在此站加过油

l=行走里程 0------->N
油量初始=P开始走   
--------------------------->


N=4,L=25,p=10
A={10,14,20,21}
B={10,5,2,4}


int  solve()
{

	//将终点站虚拟为一个节点
	A[N]=L;
	B[N]=0;
	priority_queue<int> que;
	int pos=0;int tank = P;
	int ans=0;//加油次数


	for(i=0;i<=N;i++)
	{

		//油量是否能到达第i站
		if(pos+tank>=A[i])
		{
			que.push(B[i]);
			pos=A[i];
			tank-=(A[i]-pos);
		}
		//不能到达
		else
		{
			if(!que.empty())
			{
				//加油
				tank=que.pop();
				ans++;
				i--;//中和后面i++继续探测第i站,油量增加了加了一次油

			}
			else
				break;
		}
	}

	if(i==N)
		return ans;
	else
		return -1;
}

//木板问题:huffman树建立过程考虑采用优先队列优化


int N,int L[MAX_N];

priority_queue<int,vector<int>,greater<int>> que;
for()
{
	que.push(L(i));
}


while(que.size()>1)
{
	int Lmin1=que.pop();
	int Lmin2=que.pop();

	L=Lmin1+Lmin2;
	ans+=L;
	que.push(L);


}



