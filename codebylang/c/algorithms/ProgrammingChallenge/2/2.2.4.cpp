/*************************************************************************
    > File Name: 2.2.4.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月29日 星期五 23时51分14秒
    > Update Time: 2015年05月29日 星期五 23时51分14秒
 ************************************************************************/

#include<iostream>
using namespace std;

/*
I think:直线上N个点要求最少标记点在R半径下将所有点覆盖
若贪心算法，考虑优先标记R范围内覆盖点最多的点标记

思考:贪心不仅仅是尽可能多，而是合理的尽可能的多

slove：从最左边开始寻找点首先第一个在覆盖最左边的点情况下尽可能向右覆盖，
然后此范围点被覆盖从剩下点最左边开始重复以上步骤
 *
 * */

一.
N=6
R=10

X={1,7,15,20,30,50}
flag[N]={0}
1+10 11  




i=0;

while(i<N)
{



	//覆盖i前提下向右探测找到中心
	for(j=i;X[j]-X[i]<X[i]+R;j++)
		;


	flag[j]=true;
	
	//右看，找到右边覆盖的移动i即下次视为最左边的
	for(i=j;X[i]-X[j]<X[j]+R;i++)
		;

}

二.木板切割问题:
/*  
 *
 木板切割为N块 L1,L2,LN,怎样切割开销最小

 构造切割二叉树，叶子节点对应了切割出的木板， 开销= 叶子节点深度×木板长度
 所以最佳切割应保证长度小节点深度深，长度大的节点深度浅
 考虑huffman树
 *
 */


typedef long long ll;

int N;
int L[MAX_N];




void solve()
{
	ll ans = 0;

	int min1=0,min2=1;
	while(N>1)
	{
		i=min1;
		j=min2;

		i=findmin1(L,i,min2); //start
		j=findmin2(L,j,min2+1);//

		if (i!=min1) swap(L,min1,i);
		if( j!=min2) swap(L,min2,j);  
		
		//将次小，最小换到最前面

		int temp=L[min1]+L[min2];
		ans+=temp;

		min1++;
		L[min2++]=temp;

		N--;
		

	}

}
