"""
postorder: dfs搜索完成时间, 后完成排后面
reverse postorder
"""

assume RPO is vector

def search(n):
    mark n visted
    #遍历n的后继节点
    for next node s of n:
        if s is unvisted:
            T.append(n->s)
            search(s);
    # 逆后续先完成的排在后面
    RPO[n] = N
    N = N-1

def RPO(CFG):
    DFSTREE T = []  #边集
    for node n in CFG:
        mark n unvisted
    N = |CFG|
    n0 = CFG.entry
    search(n0)
