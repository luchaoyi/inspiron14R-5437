/*************************************************************************
    > File Name: EightQueen.c
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年05月26日 星期二 21时12分06秒
    > Update Time: 2015年05月26日 星期二 21时12分06秒
 ************************************************************************/

#include<stdio.h>

//row 起始行
//列数
void EightQueen(int row,int n,int (*chess)[8])
{
	int chess2[8][8];

	for (i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
			chess2[i][j]=chess[i][j];
	}

	if(8 == row)
	{
		//print
	}

	else
	{
		//判断危险
		
		//深度优先递归
		/*                1 2 3 4 5 6 7 8
						1 
						2
						3
						4
						5
						6
						7
						8
		 */
		for(j =0;j<n;j++)
		{	
			if (notDanger(row,j,chess))
			{

				for (i=0;i<8;i++)
				{
					*(*(chess2+row)+i) = 0; //清空上次结果
				}

				*(*(chess2+row)+i) = 1;
				//深度优先
				EightQueen(row+1,n,chess2);
			}
		}
		 
	}


}

int main()
{
	int chess[8][8],i,j;
	for (i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
			chess[i][j]=0;
	}

	EightQueen(8,8,chess);
}
