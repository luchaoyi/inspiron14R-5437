/*************************************************************************
    > File Name: 4.5.1.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年06月14日 星期日 15时21分15秒
    > Update Time: 2015年06月14日 星期日 15时21分15秒
 ************************************************************************/

#include<iostream>
using namespace std;


/*  剪枝
 *
 * 数独:
 *
 * 9*9 :考虑从左上角开始深度优先搜索:剪枝则用行，列，3×3方块没有出现过的数字
 * 16*16 空白太大 ，则复杂度太高，考虑进一步优化
 * （1）考虑每一行时：只有一个空格，或一个可选数字时优先处理，可以提前发现问题
 * （2）调整搜索顺序：优先搜索可能情况少的格子
 *
 *
 * //可以看到所有搜索问题都是从穷举开始考虑剪枝
 * 火柴棒问题：
 * 1.首先考虑每个棒有移除不移除两状态:穷举搜索
 * 2.剪枝优化：
 * 考虑棒棒移除后不会破坏任何正方形则不移除,
 * 所有待选火柴棒移除也还有正方形则停止搜索,（无效解）
 * 设置最优解记录如果，此时移动数已经大于最小值则停止
 *
 *
 *  */

int M,S;

bool m[MAX_MATCH][MAX_SOUARE];  //m[i][j] = 1; 火柴i 属于正方形j
int mmax[MAX_SOUARE]; //正方形i火柴最大编号


//优化剪枝：更快发现下界 当前移除火柴数+（剩余正方形）/（一根火柴破坏最多正方形数）

int min_res
//p是火柴棒号，num是移除次数 state 是正方形
int dfs(int p,int num,vector<bool> state)
{
	if(p == M) return min_res==num;

	if(num >= min_res) return INF; //停止

	bool use = false; //一定移除 true 
	bool notuse = true; //一定不移除 true

	
	//考察每个正方形
	for(i=0;i<S;i++)
	{   
		//破坏正方形 可以移除
		if(state[i] && m[p][i]) notuse=false;


		//如果只剩p则必须移除 从小到大考察 p是最大编号时
		if(state[i] && mmax[i] == p) use=true;

	}

	int res = INF;
	//不移除 p
	//use = false 是不移除 or 移除  
	if(!use) res = min(res,dfs(p+1,num,state));
    
	//else use=true 必须的 + 上面的 or 
	//移除p的
	for(int i = 0 ;i<S;i++)
	{
		if(m[p][i]) state[i] = false;
	} 

	//不是必须移除 尝试移除
	if(!notuse) res = min(res dfs(p+1,num+1,state));

	//如果 for 执行了移除 notuse=true则矛盾了，这里自然也没有在递归下去返回了
	return res;


} 
