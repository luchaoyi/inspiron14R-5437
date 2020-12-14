/*************************************************************************
    > File Name: 1.1.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月28日 星期四 22时18分42秒
    > Update Time: 2015年05月28日 星期四 22时18分42秒
 ************************************************************************/
//优化 n^4 -> n^3logn -> n^2logn
#include<cstdio>
#include<iostream>
using namespace std;

/*
 
  写有n个纸片的数字取四次（有放回取）和为m则 yes！
 
 
 * */

//eg:
//n=3
//m=9
//k={1,3,5}


const int MAX_N = 50;

int main()
{

	int n,m,k[MAX_N];


	//scanf ->k
	//
	
	bool flag=false;

	for(i=0;i<n;i++)
	
		for j
			for p 
				for q
					if(  m == k[i]+k[j]+k[p]+k[q])
						f=true;

	if(f==true)
		puts("yes!");

	puts("no!");

	return 0
	
}

//优化 m=a+b+c+d d=m-a-b-c 检查k中的元素是否=m-a-b-c
 

bool search(d)
{
	int l=0,r=n;

	while(r-1>=l){

		(0+4)/2=2 0 ,1,2,3
		(0+5)/2=2 0 ,1,2,3,4
		int i=(l+r)/2;
		if(k[i] == x) return 1;

		else if(k[i]<x)
			l=i+1;
		else
			r=i;


		return false;

	}
}


int main()
{

	int n,m,k[MAX_N];


	sort(k,k+n);//两个地址
	//scanf ->k

	bool flag=false;

	for(i=0;i<n;i++)
	
		for j
			for p //优化这里 
				int d =k[i]+k[j]+k[p];
				f=search(d);//二分查找

	if(f==true)
		puts("yes!");

	puts("no!");
	return 0
	
}

//进一步优化 c+d = m-a-b ,先枚举算出c+d所有值 n^2 在二分搜索 
//


int kk[MAX_N*MAX_N]


void solve(){

	for c
		for d 
			kk[c*n+d]=k[c]+k[d];
	sort(kk,kk+n*n);

	
	for a
		for b
			f=search(m-k[a]-k[b]);
}
