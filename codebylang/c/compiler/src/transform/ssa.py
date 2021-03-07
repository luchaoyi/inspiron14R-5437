""""
SSA转换
G.求支配集idom 
    迭代集合运算/DFS的方法(效率更高)
2.求支配df
3.生成PHI函数
4.变量重命名(变量每一次定值都增加版本号)
"""

#为cfg每个节点求支配边界
#支配边界即节点不能支配的节点
#df支配边界集
#idom支配集
def function Idom(cfg g):
    for each node b in g
      #节点直接前驱大于2,即有多个路径到达此节点b
      if the number of immediate predecessors of b ≥ 2
        for each p in immediate predecessors of b
          runner := p
          #b是直接其前驱p以及p的支配节点的支配边界，且这些节点都不是b的支配节点
          while runner ≠ idom(b)
            #将节点b加入到runner的支配边界集合
            #每一个有多个分支的节点，都是直接前驱的支配边界
            add b to runner’s dominance frontier set  #add b in df(runner)
            #考察p的支配节点
            runner := idom(runner)

#PHI函数添加
def function Gen_Phi:
    #为cfg入口定义的每一个变量执行一次Place-phi-function 
    for all variables x in the flow graph do
        Place-phi-function(v)

"""
优化：仅为属于全局名字的变量执行palce phi，因为仅在单个基本块内活跃的变量不必要
"""
def function Gen_Phi:
    Globals = []
    Blocks = {} # key是变量 value是block list

    #寻找全局名字
    for b in all blocks:
        VarKill = []
        for op_i in b.oplist:
            # assume op_i is x <- y op z
            if y not in VarKill:
                Globals.append(y)
            if z not in VarKill:
                Globals.append(z)
            VarKill.append(x)
            Blocks[x].append(b) #存储了对x定值的块
    
    for x in Globals:
        WorkList = Blocks[x]
        for b in WorkList:
            #块b是对全局名字x定值的块，在它的支配边界节点放置x的phi函数
            #在全局名字被定值节点的支配边界放置变量的phi
            for d in DF(b):
                if d has no phi-function for var x:
                    Place-phi-function(x)
                    WorkList.append(d) #放置phi相当于x定值，因此d也加入worklist

# has-phi(B) is true if a φ-function has already been placed in B
# processed(B) is true if B has already been processed once for variable v
# Assignment-nodes(v) is the set of nodes containing statements assigning to v
# W is the work list (i.e., queue)
#为变量v在cfg节点中添加PHI函数
"""
为变量v放置phi
1.找出对所有对v def 的节点集合S
2.对S中每一个节点B，在B的支配边界放置phi节点
"""
def function Place-phi-function(v):
  #init 
  for all nodes B in the flow graph do
    has-phi(B) = false;  
    processed(B) = false;  
  end for
  W = ∅; 

  #将cfg中所有对变量定值过的节点加入W
  for all nodes B ∈ Assignment-nodes(v) do     
    #processed(B)标记了对v定值的节点是否存在于W中
    processed(B) = true; 
    Add(W, B);
  end for

  while W != ∅ do
  begin
    #从W取出一个node B为对v定值的节点
    B = Remove(W);
    #在B的所有支配边界节点y放置phi函数
    for all nodes y ∈ DF(B) do
      #放置过的节点不再放置,仅处理没有为v生成过PHI的节点
      if (not has-phi(y)) then
      begin
        place < v = φ(v, v, ..., v) > in y;
        has-phi(y) = true;
        #放置v=phi(...)函数为节点y生成了一个对v定值的语句
        #因此如果y不在W中则将它放入w并set processed(y) = true;
        if (not processed(y)) then
        begin 
          processed(y) = true;
          Add(W, y);
        end
      end
    end for
  end
end


def function Rename-all-variables:
    begin 
      #对所有变量重命名
      for all variables x in the flow graph do
        V = ∅; 
        v = 1; 
        push 0 onto V;
        Rename-variables(x, Start);
      end for
    end

#def 定值
#use 使用
#图的深度优先遍历原则
function Rename-variables(x, B)  // x is a variable and B is a block
begin
  ve = Top(V);  // V is the version stack of x

  #处理B中的语句
  #普通语句的LHS和RHS,PHI语句的LHS
  for all statements s ∈ B do 
    # LHS = RHS

    # s为对x的use，且语句非PHI，x在RHS，替换右部x为当前使用的版本号 
    if s is a non-φ statement then 
      replace all uses of x in the RHS(s) with Top(V);

    # s为对x的def，即x = ...,x is LHS,使用xv替换x，v为新生成的版本号
    # 注意v比Top(V)新
    if s defines x then
    begin
      replace x with xv in its definition; 
      push xv onto V;  // xv is the renamed version of x in this definition
      v = v + 1;  // v is the version number counter
    end
  end for

  #处理B后继节点的PHI函数的RHS
  for all successors node_s of B in the flow graph do
    #对于后继节点node_s，先确定B为它的第几个前驱，这个决定了需要替换PHI函数中的第几个x变量
    #对于x = φ(x, x, ..., x),仅替换PHI的x，LHS的x是对x的def，直到处理到节点node_s时才替换
    j = predecessor index of B with respect to node_s
    for all φ-functions f in node_s which define x do
      replace the jth operand of f with Top(V);
    end for
  end for

  #基本块B已经处理完，深度优先遍历
  for all children c of B in the dominator tree do  // Depth-First Order
    Rename-variables(x, c);
  end for

  #深度搜索从B离开时，版本号回退到进入B之前的ve
  repeat Pop(V); 
  until (Top(V) == ve);
end

"""
虎书上的place phi 和rename 算法和这里的算法思想和步骤是一致的不过为不同变量使用不同的集A合和栈一次处理所有变量

"""
