#稀疏条件常量传播

#在CFG边上传递可达性，并在处理分支节点时若确定常数则将确定边放进入CFGWorkList,不确定则都放入, 边标记保证仅处理一次

#在SSA边上传递格值, 前提是当前节点的CFG边是可执行的(可达才传递数据流格值), SSA边上是没有控制流信息的要看CFG
#SSCP中 SSA Graphi由def -> use 的边组成

#传递要看CFG信息
#传递左边 -> 求值 -> 更新右边 ->为右边生成新的SSA Edge

def Sccp():
    #init 
    CFGWorkList = [离开entry n0的边]
    SSAWorkList = []
    for e in CFG:
        mark e unexecuted
    for each def and use x:
        Value(x) = Top 

    #迭代
    while CFGWorkList is not empty or SSAWorkList is not empty:
        #沿着CFG对到达节点求值，到达节点根据SSA edge 传递其它节点求值的格值信息到自身，然后进一步计算，并生成新的SSA edge
        #根据已知的常量求值信息，沿着CFG探索可达性
        #并根据探索已知可达信息和已经生成的SSA edge执行求值和常量传播并生成新的SSA edge
        if CFGWorkList is not empty:
            e(m,n) = CFGWorkList.pop()
            if e is unexecuted:
                mark e(m,n) executed
                EvaluateAllPhiInBlock((m,n))
                if 没有进入n的其它边标记为executed:
                    if n is an assignment: #n里面没有branch
                        EvaluatedAssign(n) 
                        add(n,o) in CFGWorkList #o is n的cfg后继节点 
                    else 
                        EvaluatedCond(n) #n里面有branch

        #根据探索已知可达信息和已经生成的SSA edge执行求值和常量传播并生成新的SSA edge
        if SSAWorkList is not empty:
            e(s,d) = SSAWorkList.pop()
            c = CFG node that uses d 
            # s已经求出，可以传播到d，def-use, 若use d的node已经发现可达则传递-求值
            if any edge entering c is mark executed: #c 可达的
                if d is phi func argument:
                    EvaluatePhi((s,d));
                else if c is assignment:
                    EvaluatedAssign(c)
                else:
                    EvaluatedCond(c)

/*
s: x = 1
|
d: br x 
*/
def EvaluatedCond(n)：
    let(s,d) is SSA edge ref in n #n 的branch指令依赖的值传递自s，即在s求值，在d引用， 分支依赖于value(d)
    if value(d) != botom:
        Value(d) = Value(s) #传递
        if Value(d) == botom: #非常量，所有边加入
            for each cfg edge (n, oi)
                add (n, oi) in CFGWorkList
        else 
            #常量
            let(n, om)是匹配Value(d)跳转b模板的CFG edge
            add (n,om) in CFGWorkList

def EvaluatedAssign(n)：
    #传递
    for each value y used by expr in n:
        let (x,y) is SSA edge  that supplies y #提供y的边, x->y
        Value(y) = Value(x) #沿着SSA边传播格值, x->y def-use

    #计算
    #d = y0 op y1 op y2 ...
    let d be the name of the value produced by n
    if Value(d) != botom:
        # 所有的y格值传递完成，则根据运算规则计算格值
        v = evaluation of n over lattice values #对phi函数按格值计算规则所有参数meet运算求值
        if v !=Value(d) :
                Value(d) = v #更新d的格值
                for every ssa edge (d,u) 
                    add(d, u) to SSAWorkList #根据def->use关系，生成新的SSA edge

def EvaluateAllPhiInBlock((m,n)): #(m,n) is a edge in cfg
    for each phi func p in block n:
    # 首先要传递p0,p1,p2...的格值，完成格值传递后面才可以计算结果的格值
        EvaluteOprands(p)
    for each phi func p in block n:
        EvaluteResult(p)

#求值p，先传播参数格值，再计算def的值
def EvaluatePhi((s,d)): #(s,d) is an SSA graph edge
    let p is the phi func that uses d #phi p(...d,..)
    EvaluateOperands(p)
    EvaluateResult(p)

#传递
def EvaluateOperands(phi):
    # x = phi(p0，p1，p2,...)
    # 传递pi的格值为s为了计算x,若x为底格则没有必要计算x，不需要传递到参数pi
    if Value(x) != Bottom:
        for pi in phi:
            let c = pi对应的CFG edge边
            let <a,pi> is the ssa edge ending in pi #
            #能沿着SSA边参数pi def传递到phi中的use位置的前提是，pi对应的CFG边c是可执行的, 即可达才传递
            #如果在常量传播中发现边c不可执行，则不传播
            if c is executed:
                # 沿着边def-use SSA边 a->pi 传递格值到pi
                Value(pi) = Value(a) 
#计算
def EvaluateResult(phi):
   # x = phi
    if Value(x) != Bottom:
        v = evaluation of phi over lattice values #对phi函数按格值计算规则所有参数meet运算求值
        if Value(x) != v :
            Value(x) = v  #计算处的格值更新x的格值
            for each SSA graph edge (x,y): #生成新的SSA def-use edge x->y
                add (x, y) in SSAWorkList
