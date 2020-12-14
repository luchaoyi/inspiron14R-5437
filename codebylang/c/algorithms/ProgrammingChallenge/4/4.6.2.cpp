/*************************************************************************
    > File Name: 4.6.2.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年06月15日 星期一 07时55分03秒
    > Update Time: 2015年06月15日 星期一 07时55分03秒
 ************************************************************************/

#include<iostream>
using namespace std;

/*	
 *	i<j ai>aj 对数
 *	分治法统计逆序对数列：
 *	二分 总量 = 前数列 +后数列量 + i在前数列，j在后数列量
 *				递归/   \    /      \
 *
 *
 *
 * 二分统计后前一半，后一半合并应排序，避免重复计算
 *	*/


//划分为相同子问题，然后处理不同子问题之间问题 分治
int cnt(vector<int> &a)
{
	int n = a.size();

	if(n<=1) return 0;

	ll cnt = 0;

	vector<int> b(a.begin(),a.begin()+n/2);
	vector<int> c(a.begin()+n/2,a.end());

	cnt += cnt(b);
	cnt += cnt(c);

	int ai=0,bi=0,ci=0;
	while(ai < n)
	{
		if(bi < b.size() && (ci == c.size() || b[bi] <= c[ci]))
		{
			a[ai++] = b[bi++];
			
		}
		else
		{
			cnt+=n/2-bi;
			a[ai++] = c[ci++];
		}
	}
	return 

}
