/*************************************************************************
    > File Name: 3.2.2.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年06月04日 星期四 20时49分23秒
    > Update Time: 2015年06月04日 星期四 20时49分23秒
 ************************************************************************/


#include<iostream>
using namespace std;

/*反转(开关问题) 
 *
 * N头牛 排列机器使k头连续牛转向求最少操作次数M和对应的K
 *
 * 思考给定k，如何让牛超前的最小操作数(注意这个解决问题的方法，整体解不出来就分步）
 * 求解上问题后可以采用搜索法来求出最小k
 * 
 * 每次反转k头，反转区间顺序没有影响,一个区间只能反转一次
 *
 *
 * 从最左开始 若牛B反转k个区间考察后面的牛B则反转F的不反转
 *
 * ans=0
 * for(i=0;i<n-k;i++)
 * {
 *	if(cows[i] == "B")
 *	反转复杂度not(f);
 *		ans++;
 * }
 *for(++i;i<n;i++)
	if(cows[i] ==B )
		return -1;:
 *  */



int N;
int cows[MAX_N] //牛方向(0:F,1:B)


//注意优化在这里不反复的反转cows数组而采用f[MAX_N]记录是否反转最终统计
//对于第i头牛sum(i)=f(i-k+1)+....f(i-1)为奇数则与起始方向相反
//																头	 +   尾
//第i+1头 sum(i+1)=f(i+1-k+1)+...f(i+1-1)  sum(i+1) = sum(i) -f(i-k+1)+f(i)  
//int f[MAX_N] ;//记录区间[i,i+k-1]是否反转过 反转过1,没有0

//固定k
int calc(int K)
{
	memset(f,0,sizeof(f));
	int res=0;

	int sum=0;
 
	for(int i=0;i+k<N;i++)
	{
		//0(F)+sum为偶数时原方向=偶数 
		//1（B)+sum奇数反转过=偶数    
		if((cows[i]+sum)%2 !=0)//反转
			{
				res++;
				f[i]=1;
			}

		sum+=f[i];
		if(i-k+1>=0)
			sum-=f[i-k+1];
	}

	for(i=N-K+1;i<N;i++)
	{
	
		if((cows[i]+sum)%2 !=0)
		{
			return -1;
		}
	}
	if(f[i-k+1]>=0)
	{
		sum -=f[i-k+1];
	}


}

//后面最小k只需搜索k=0-->N比较get

//样例2
//

const int dx[5]={-1,0,0,0,1};
const int dy[5]={0,-1,0,1,0};

int M,N;

int tile[MAX_N][MAX_N];
int opt[MAX_N][MAX_N];
int filp[MAX_N][MAX_N];//统计格是否反转过

//查询颜色
int get(int x,int y)
{
	int c=tile[x][y];

	//上下左右中五格是否反转过
	for(int d=0;d<5;d++)
	{
		int x2=x+dx[d];
		int y2=y+dy[d];

		if(0<=x2 && x2<M && 0<=y2 && y2 <N)
		{
			c+=filp[x2][y2];
		}

	}

	return c%2;
}

int calc()
{
	//指定尽量从下格反转,从第二行开始
	
	for(int i=1;i<M;i++)
	{
		for(int j=0;j<N;j++)
		{
			//i,j是否反转取决于 正上方i-1,j
			if(get(i-1,j)!=0)
				flip[i][j]=1;
		}
	}


	//判断最后一行
	for(int j=0;j<N;j++)
	{
		if(get(M-1),j!=0)
		{
			return -1;
		}

	}


	//统计反转次数
	int res=0;
	for
		for
			res+=flip[i][j];
}
