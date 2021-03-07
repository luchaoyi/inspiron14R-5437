//基于回溯的图着色
bool isSafe(int v, bool graph[V][V], int color[], int c)////用于检查当前颜色分配的实用程序函数
{
    for (int i = 0; i < V; i++)
 
    if (graph[v][i] && c == color[i])
        return false;
    return true;
}
 
void graphColoring(bool graph[V][V], int m, int color[], int v)//求解m着色问题的递推效用函数
{
 
    if (v == V)//基本情况：如果所有顶点都指定了颜色，则返回真
    {
        printSolution(color);
        return;
    }
    /* 考虑这个顶点v并尝试不同的颜色*/
    for (int c = 1; c <= m; c++)
    {
        /* 检查颜色C到V的分配是否正确*/
        if (isSafe(v, graph, color, c))
        {
            color[v] = c;
            /* 递归为其余顶点指定颜色 */
            graphColoring(graph, m, color, v + 1);
            /* 如果指定颜色C不会产生解决方案回溯 */
            color[v] = 0;
        }
    }
}
