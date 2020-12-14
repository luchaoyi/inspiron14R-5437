/*************************************************************************
    > File Name: 2.1.4.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月28日 星期四 23时09分17秒
    > Update Time: 2015年05月28日 星期四 23时09分17秒
 ************************************************************************/


#include<iostream>
using namespace std;

/*
 * DFS :搜索算法时首先明确问题状态，后考虑搜索优化
 */

/*
 *a1,..an中选择若干个数恰好组成k
 *状态每个数有两个状态选或不选
 *
 *
 **/


//搜索剪枝 ：在搜索中若当前状态sum已经>k以后则不会在=k
int a[MAX_N]
int n,k;


bool dfs(int i,int sum){


	if(sum > k) return false;//剪枝
	//if(sum == k) return true;

	if(i == n) return sum==k;

	if(dfs(i+1,sum+a[i])) return true;
	if(dfs(i+1,sum)) return true;


	return false;

}

