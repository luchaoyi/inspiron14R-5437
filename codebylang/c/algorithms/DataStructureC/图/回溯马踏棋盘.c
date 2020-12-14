/*************************************************************************
    > File Name: DFS.c
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月26日 星期二 20时42分56秒
    > Update Time: 2015年05月26日 星期二 20时42分56秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>

#define X 8
#define Y 8


int chess[X][Y];



/*
 *     \ | /
 *   ---  ---
 *		/|\
 * */
int nextxy(int *x,int *y,int count)
{
switch(count)
	{
		case 0:
			if (*x+2 <=X-1 && *y-1>=0  && chess[*x+2][*y-1] ==0 )
			{
					*x+=2;
					*y-=1;
					return 1;
			}
			break;

		case 1:
			//...

		default:
			break
	}
return 0;
}

//深度优先
//tag 标记
int TravelChessBoard(int x,int y,int tag)
{
	int x1=x,y1=y,flag=0,count=0;


	chess[x][y]=tag;

	if(tag == X*Y)
	{
		//print chess
		return 1;
	}

	//找马下一个坐标
	//递归
	//
	flag =nextxy(&x1,&y1,count);
	while(0==flag && count<7)
	{
		count++;
		flag=nextxy(&x1,&y1,count);
	}

	//成功则深度搜索
	while(flag)
	{

		if(TravelChessBoard(x1,y1,tag+1))
			return 1;
	}

	//失败
	if(0==flag)
	{
		chess[x][y] == 0;
	}

}
