def MarkBlcok(loopblocks, entry, i, nblocks, ninsts):
    for j = 1 to ninsts[i]:
        if !InstInvar[i][j]:
            Inst =loopblocks[i][j]
            switch (Inst.kind):
                case binexp:
                    #判断两个操作数是否三个满足条件
                    #mark前要进行到达定值数据流分析
                    if opr1... f1 = true else false
                    if opr2...  f2 = true else false
                    InstInvar[i][j] = f1 && f2
                case unary 
                    ...
            if InstInvar[i][j]:
                InvarOrder.append(<i,j>)
                change = True

#标识了循环不变量指令
def MarkInvar(blocks, entry, nblocks, ninsts):
    # init InstInvar 记录指令是否为loop const var
    for i = 1 to nblocks:
        for j = 1 to ninsts[i] :
            InstInvar[i,j] =  False

    change = False
    do:
        # BFS序迭代
        for i in BFSOrder(loopblcoks, entry):
            change = MarkBlock(loopblocks, en ,i, nblocks, ninsts)

    while change

#标识后将满足条件的指令提到prehead节点
