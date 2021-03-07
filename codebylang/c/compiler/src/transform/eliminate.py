"""
无用代码消除使用类似垃圾回收的标记清除过程
消除后可能会包含空基本块，通过消除无用控制流
"""

def CodeEliminate():
    Mark()
    Sweep()

def Mark():
    WorkList = []
    # 首先标记关键op,关键op是绝对有用的代码它们是遍历的根节点
    for op_i in Module.OpList:
        if op_i is critical:
            mark op_i
            WorkList.append(op_i)
    
    while !WorkList.empty:
        op_i = WorkList.pop(), assume op_i is x <- y op z
        # op_i是有用的，根据use-def传播到普通指令
        if !def(y).marked:
            mark def(y) 
            WorkList.append(def(y))
        if !def(z).marked:
            mark def(z) 
            WorkList.append(def(z)) 

        # op_i是有用的，根据控制依赖传播到branch指令
        for b in RDF(block(op_i)):
            let op_j  be the branch that ends b and unmarked
            mark op_j
            WorkList.append(op_j)

def Sweep():
    for op_i in Module.OpList:
        if !op_i.marked: 
            if op_i is a branch: #重写没有标记的branch
                rewrite op_i -> jump to 有标记有用的最近后向支配节点
            if op_i is not a jump：
                delete op_i
