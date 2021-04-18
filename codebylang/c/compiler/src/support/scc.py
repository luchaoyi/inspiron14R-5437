""""强连通分量
顶点u<->v v<->u都有路径则顶点强连通，强连通顶点子图为强连接连通分量

根据定义求法 ：双向遍历求交集
"""
#鲸书163 Tarjian算法寻找极大SCC

#Tarjian 同处于一个SCC中的结点必然构成DFS树的一棵子树,我们要找SCC，就得找到它在DFS树上的根
#dfs树上以u根节点子树，u的dfs序号时最小的
#当遍历完一个节点u的子树时，u要回溯了，此时若dfn(u) == low(u) 则u到栈顶组成了一个强连通分量
#u到栈顶是它的子孙节点
#low[i],反映的时当前点通过自己的非树边或子树中的非树边，能连接到离根最近的祖先节点（此路径构成了一个环路）

stack<int> s;
int dfn[10001], low[10001], sum = 0;
results =[];


void tarjan(int u):
    #通过树边向更深搜索时dfn一直时增大的, (第33行)当遇到已经在栈中的父节点时 祖先->...子孙->祖先形成了一个环路
    #此环路形成一个scc，由于祖先dfnz更小，因此回溯时祖先的序号沿反方向<-...<-传播到路径上的low[i]
    # v->..i..->v ,最终此环路所有节点low[i] = dfn[v], 当回退到v时，low[v] = dfn[v],此scc被发现
    dfn[u] = low[u] = ++sum; 

    s.push(u);
    #这里visit表示释放在栈中
    visit[u] = true;
    for (遍历与u相邻的v) {
        #dfn(v) is 0保证初次访问,且仅dfs搜索一次
        if !dfn(v) {
            tarjan(v)
            low[u] = min(low[u], low[v]);  #反向回退时将low[v]传播给low[u]
            }  

        #v已经访问过，说明u->v不是前向边, 若dfn序号更小且在栈中则通过后向边访问到了祖先
        #更新low[u]为dfn[v],并通过后续到倒退将dfn[v]一路反向传播到v节点
        #自v开始形成的环路的low[i]都被染成了dfn[v]
        else if(visit[v]) low[u] = min(low[u], dfn[v]);
    }

    #叶子节点首先直接执行到这里了
    if (low[u] == dfn[u]) {
            int j;
            scc = [];
            do {
                #出栈，visit表示是否在栈中
                j = s.top();
                s.pop();
                visit[j] = false; 
                scc.append(j);
                } while(j!=u);
        #生成一个scc
        results.append(scc);
    }

/*
例子：
SCC A->B->C->D->A
开始dfs搜索:
dfn 1 2 3 4  
low 1 2 3 4
D -> A遇到else if visit[A] is true 
low D is equal to dfn[A] is 1
dfs返回时, 1沿着链路回传
low 1 1 1 1
此时栈中[4,3,2,1]，的low[i]都为1，发现了从1到栈顶的一个SCC环路
*/


