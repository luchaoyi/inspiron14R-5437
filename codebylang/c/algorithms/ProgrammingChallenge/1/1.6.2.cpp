/*************************************************************************
    > File Name: 1.6.2.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月27日 星期三 22时56分38秒
    > Update Time: 2015年05月27日 星期三 22时56分38秒
 ************************************************************************/

#include<iostream>
using namespace std;

/*
   蚂蚁最短应该是离哪边近就朝哪个方向走，以不冲突时间最短时间
   不存在冲突
   思想最长应该是相反的

   <----- ----->
   最长的考虑:

   若A，B相冲突 
   A--> <---B    AB        <--AB--->若无视不同蚂蚁区别
   <----BA---->相当于蚂蚁穿过去了
   所以最长时间是每个蚂蚁最长的最长距离即蚂蚁选择
   这里也证明了上面的思想



  */


//     左---------------------------------
int L=10
int n=3
int x[MAX_N]={2,6,7}

void solve()
{
	
	//最短时间取决于最短爬向中最远的蚂蚁
	

	for(i=0;i<n;i++)
	{

		minT = max(minT,min(L-x[i],x[i]);
	}

	for(i=0;i<n;i++)
	{

		maxT = max(maxT,max(L-x[i],x[i]);
	}


	/*
	 * 目测错了蚂蚁时间不是累加而是选择最大的
	char Direction_near[MAX_N];
	char Direction_far[MAX_N];
	int lenMax=0;
	int LenMin=0;
	for(i=0;i<n;i++)
	{
		if(L-x[i]>x[i])
		{
			Direction_near[i]='l';
			Direction_far[i] = 'r';

			LenMax+=(L-x[i]);
			LenMin+=x[i];
		}
		else
		{
			Direction_near[i]='r';
			Direction_far[i]='l';

			LenMin+=(L-x[i]);
			LenMax+=x[i];
		}
		
	}

	tmin=LenMin/V;
	tmax=LenMax/V;
	*/

}
