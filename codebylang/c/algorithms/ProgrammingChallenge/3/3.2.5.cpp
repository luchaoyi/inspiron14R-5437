/*************************************************************************
    > File Name: 3.2.5.cpp
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年06月06日 星期六 17时17分46秒
    > Update Time: 2015年06月06日 星期六 17时17分46秒
 ************************************************************************/

#include<iostream>
using namespace std;


/* 
 求被划分趋于个数，采DFS搜索，将划分线当作强，从某个未被搜索过的块DFS，几次DFS，几个区域

 but格太大了所以要压缩格，数
 删除前后没有变化的格子并不影响结果
 */
