/*************************************************************************
    > File Name: 4.1.1.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年06月04日 星期四 22时09分09秒
    > Update Time: 2015年06月04日 星期四 22时09分09秒
 ************************************************************************/

#include<iostream>
using namespace std;

/* 样例2：期望步数
 每一次等概率上下左右移动求从(0.0出发移动到（N-1,M-1)期望步数

 表示x，y到达终点的期望步数
 E(x,y) = 1/4E(x-1,y)+1/4E(x+1,y)+1/4E(x,y-1)+1/4E(x,y+1)
 E(N-1,M-1)=0
 E(石头)=0 E(无法到达的点)=0
 联立方程组求解
 */

char grid[MAX_N][MAX_N];
bool can_goal[MAX_N][MAX_N];
//u d l r
int dx[4]={-1,1,0,0},dy[4] = {0,0,-1,1};

//遍历能达到的都置1
void dfs(int x,int y)
{
	can_goal[x][y] = true;
	for(i=0;i<4;i++) //上下左右?
	{
		int nx=x+dx[i],ny=y+dx[i];
		if(0<=nx && nx <N && 0<=ny && ny< M && !can_goal[nx][ny]&&grid[nx][ny]!='#' )
			dfs(nx,ny)
	}
}

void solve()
{

	//init
	
	for
		for
			can_goal[i][j]=false;

	dfs(N-1,M-1);

	...
	//解方程

}


