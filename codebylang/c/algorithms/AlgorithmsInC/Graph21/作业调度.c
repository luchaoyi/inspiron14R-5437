/*************************************************************************
    > File Name: 作业调度.c
    > Author: luchaoyi
    > Mail: 751714700@qq.com 
    > Created Time: 2015年01月16日 星期五 14时28分41秒
    > Update Time: 2015年01月16日 星期五 14时28分41秒
 ************************************************************************/

#include<stdio.h>

/*
 * 作业调度可以归约为差分约束
 * 节点为开始时间路径为作业持续时间
 *可以归约为无环网中的最长路径问题
 无环是因为不存在开始时间小于自身的节点 不能绕回去
 最长路径 是因为开始作业时间取决与入度最后完成

 虚拟一个节点到其它所有节点路径为0 find一条最长路径
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * */
