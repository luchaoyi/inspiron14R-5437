/*************************************************************************
    > File Name: 3.1.3.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年06月02日 星期二 20时11分09秒
    > Update Time: 2015年06月02日 星期二 20时11分09秒
 ************************************************************************/

#include<iostream>
using namespace std;


/*  
 *  牛舍问题
 *  */

//构造判断：要求最大化两头牛距离是所以两头牛距离是搜素目标
//这里的判断自然构造为距离为d是否符合约束

M=3; //牛数
N=5; //牛舍数
int x[MAX_N]
bool C(int d)
{
	int last=0;
	for(i=1;i<M;i++)
	{

		int crt = last+1;
		while(crt<N && c[crt]-x[last] < d)
			crt++;

		if(crt == N) return false;
		last=crt;
	}

	return true
}

//then 二分搜索 lb=ub;
