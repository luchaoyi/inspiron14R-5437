/*************************************************************************
    > File Name: 2.3.1.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月30日 星期六 12时08分07秒
    > Update Time: 2015年05月30日 星期六 12时08分07秒
 ************************************************************************/

#include<iostream>
using namespace std;

/* 背包问题，搜索解法
 * */


N=4;
//(w,v)={(2,3),(1,2),(3,4),(2,2)}

WEIGHT[N]= ...;
VALUE[N] = ...;
W=5;



/*
init:
	(5,0)
   /    \
   (3,2) (5,0) //物品1
   /   \ /   \ //select or not select
   ...

   if (a,b).a == 0 stop return
   */


/*我的思考c:w
 *
 * */
int SMAX[MAX_N] = {0};
int VMAX = 0 ;
//搜索物品i
void search(i,W,V,f)
{

	//停止搜索统计结果    //剪枝
	if(W<=0 || i==n ) 
	{
		if (V > VMAX)
		{
			VMAX = V;
		    load(SMAX,S); 
			return;
		}
	}

	if (f==1) 
	{
		S[i]=1;
		W-=WEIGHT[i];
		V+=VALUE[i];
	}
	else 
	{
		S[i]=0;
	}

	search(i+1,W,V,1);
	search(i+1,W,V,0);
}

//参考答案:

int dp[MAX_N][MAX_N]; //memset(dp,-1,sizeof(dp)) -1==11111111填充内存 000000000也可以但并不可以 0000 0001这样


int rec(int i,int j)
{

	if (dp[i][j] >=0)
	{
		return dp[i][j];
	}
	//优化，递归时保存已计算过的数据避免重复计算很重要
	
	int res;
	if(i==n)
	{
		res=0;
	}
	//这个判断上面没有写
	else if (j < w[i])
	{
		res=rec(i+1,j);

		//不能选择i容量太小
	}
	else
	{
		//select or not 
		res=max(rec(i+1,j),res(i+1,j-w[i])+V[i]);
	}
	
	return dp[i][j] = res;

}


dp[MAX_N][MAX_N]={0};
//dp 
solve()
{
	//dp[n][j] = 0; 
	//决策是选或不选，递推
	for(i=n-1;i>=0;i--)
	{
		for (j=0;j<=W;j++)
		{
			if (j<w[j])
			{
				d[i][j] = dp[i+1][j];
			}
			else
				dp[i][j] = max(dp[i+1][j],dp[i+1][j]+V[i]);
		}
	}

	return dp[0][W]
}


// LBS问题
//
int n,m;
char s[MAX_N],t[MAX_N];

int dp[MAX_N+1][MAX_N+1]; 

//dp是序列的长度
//dp[n][m] 代表着 串's1,s2,...sn'与串't1,t2,...tm'公共子序列长度
//dp[n+1][m+1] 都加长一个 if Sn+1=Tn+1  dp[n+1][m+1] = dp[n][m] +1
void solve()
{

	for(int i =0;i<n;i++)
	{
		for(int j = 0;j <m;j++)
		{
			if(s[i]== t[j])
			{
				dp[i+1][j+1] = dp[i][j]+1;
			}
			else
			{
				dp[i+1][j+1] = max(dp[i][j+1],dp[i+1][j]);
			}
		}
	}
}
