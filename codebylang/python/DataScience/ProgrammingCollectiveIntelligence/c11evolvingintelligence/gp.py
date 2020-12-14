#-*-coding:utf8-*-

#遗传编程：利用遗传计算技术，自动生成解决问题的程序(构造算法的算法)
#个体是真正的程序，随机生成的程序，自行构造的程序，不是随机生成的字符串


from random import random,randint,choice
from copy import deepcopy
from math import log

class fwrapper:
    def __init__(self,function,childcount,name):
        self.function=function
        self.childcount=childcount
        self.name=name


class node:
    def __init__(self,fw,children):
        self.function=fw.function
        self.name=fw.name
        self.children=children

    def evaluate(self,inp):
        results=[n.evaluate(inp) for n in self.children]
        #print results
        return self.function(results)
        
    def display(self,indent=0):
        print (' '*indent)+self.name
        for c in self.children:
            c.display(indent+1)        
    

class paramnode:
    def __init__(self,idx):
        self.idx=idx

    def evaluate(self,inp):
        return inp[self.idx]
        
    def display(self,indent=0):
        print '%sp%d' % (' '*indent,self.idx)

class constnode:
    def __init__(self,v):
        self.v=v
    def evaluate(self,inp):
        return self.v
        
    def display(self,indent=0):
        print '%s%d' % (' '*indent,self.v)



#利用lambda创建

addw = fwrapper(lambda l:l[0]+l[1],2,'add')
subw = fwrapper(lambda l:l[0]-l[1],2,'subtract')
mulw = fwrapper(lambda l:l[0]*l[1],2,'multiply')

def iffunc(l):
    if l[0]>0:return l[1]
    else:return l[2]

ifw=fwrapper(iffunc,3,'if')

def isgreater(l):
    if l[0]>l[1]: return 1
    else: return 0

gtw=fwrapper(isgreater,2,'isgreater')
flist=[addw,mulw,ifw,gtw,subw]


def exampletree():

    #每一个节点包含节点类型，和孩子，内部节点都是node型，代表这一种运算，叶子节点是变量或常量
    return node(
            ifw,
            [
                node(gtw,[paramnode(0),constnode(3)]),
                node(addw,[paramnode(1),constnode(5)]),
                node(subw,[paramnode(1),constnode(2)]),
            ]

            # fun(X,Y)  x<--paramnode(0)  y<-----paramnode(1)
            #           if 
            #   l:   0      1        2
            #   [gtw    addw    subw]       
            #    X  3   Y   5   Y   2    
            #
            #
            #
            )



#fpr节点是函数型节点概率，ppr不是函数型节点时是paramnode节点概率
#pc输入参数的个数
def makerandomtree(pc,maxdepth=4,fpr=0.5,ppr=0.6):
    if random() < fpr and maxdepth>0:
        f=choice(flist)
        children=[makerandomtree(pc,maxdepth-1,fpr,ppr) for i in range(f.childcount)]

        return node(f,children)
    elif random()<ppr:
        #随机选择参数
        return paramnode(randint(0,pc-1))
    else:
        #随机生成常数
        return constnode(randint(0,10))




def hiddenfunction(x,y):
    return x**2+2*y+3*x+5

def buildhiddenset():
    rows=[]

    for i in range(200):
        x=randint(0,40)
        y=randint(0,40)
        rows.append([x,y,hiddenfunction(x,y)])

    return rows



def scorefunction(tree,dataset):
    #用所有数据测试一个程序的优劣
    dif=0
    for data in dataset:
        v=tree.evaluate([data[0],data[1]])
        dif+=abs(v-data[2])

    return dif



#变异是小更改。改变节点上函数;改变子节点数目,改变子节点，新树替换等多种方法

def mutate(t,pc,probchange=0.1):
    #probchange概率替换树，大变异
    if random()<probchange:
        return makerandomtree(pc)
    #对子节点变异
    else:
        result =deepcopy(t)
        if isinstance(t,node):
            result.children=[mutate(c,pc,probchange) for c in t.children]
        return result



def crossover(t1,t2,probswap=0.7,top=1):

    if random() < probswap and not top:
        return deepcopy(t2)
    else:

        #子节点交叉
        result=deepcopy(t1)
        if isinstance(t1,node) and isinstance(t2,node):
            result.children=[crossover(c,choice(t2.children),probswap,0)
                    for c in t1.children]

        return result


def getrankfunction(dataset):
    def rankfunction(population):
        scores=[(scorefunction(t,dataset),t) for t in population]
        scores.sort()
        return scores

    return rankfunction



#随机优化算法，为了寻优需要将当前优信息传递下去，而为了避免陷入局部最优又要使种群具有多样性
#这是一个制衡
def evolve(pc,popsize,rankfunction,maxgen=500,mutationrate=0.1,breedingrate=0.4,pexp=0.7,pnew=0.05):

    #遗传算法主程序
    #初始化种群-->淘汰-->交叉,变异-->形成新种群
    def selectindex():
        #pexp 越小 selectindex() 越小 则只选择最前面的复制概率越大
        return int(log(random())/log(pexp))

    population=[makerandomtree(pc) for i in range(popsize)]
    scoresmemory=[]
    for i in range(maxgen):
        scores=rankfunction(population)

        print scores[0][0]
        
        if scores[0][0] == 0.0: break

        #两个精英个体,其它淘汰
        newpop=[scores[0][1],scores[1][1]]
        #scoresmemory.append(scores[0])
        #print scoresmemory
        while len(newpop) < popsize:
            if random() > pnew:
                newpop.append(mutate(
                    crossover(scores[selectindex()][1],scores[selectindex()][1],
                    probswap=breedingrate),
                    pc,probchange=mutationrate ))
            else:
                #生成新的随机个体，增加种群多样性
                newpop.append(makerandomtree(pc))
                    
        
        population=newpop

    #保存每一代最优个体，最后输出最优的最优
    #scoresmemory.sort()
    print '----------------'

    #记忆的方法不适用于对奕，因为大家都变的更加优秀，不是保存某代最优，因为不断进化中,不同代之间没有比较性，所处年代不同
    #print scoresmemory[0][0]
    #return scoresmemory[0][1]
    return scores[0][1]


#游戏示例
#全局变量

#4*4
chesssize=5

def gridgame(p):
    global chesssize

    #坐标有效范围，从0开始所以-1
    max=(chesssize-1,chesssize-1)
    lastmove=[-1,-1]

    #初始两个玩家的位置
    location=[[randint(0,max[0]),randint(0,max[1])]]
    location.append([(location[0][0]+2)%4,(location[0][1]+2)%4])

    #限定移动50步，平局
    for o in range(50):
        for i in range(2):
            locs=location[i][:]+location[1-i][:]
            locs.append(lastmove[i])

            #自动学习程序，传入当前两个节点位置，即自身上次移动位置
            #p为遗传程序构造出的AI
            #学习得到移动策略
            move=p[i].evaluate(locs)%4 
            #同一个方向连续移动两次，输
            if lastmove[i]==move:return 1-i
            lastmove[i]=move

            #     0
            #   2   3
            #     1
            #    x代表列代表行y
            # 一一一>y
            # |
            # |
            # V
            # x
            if move==0: 
                location[i][0]-=1
                # Board wraps
                if location[i][0]<0: location[i][0]=0
            if move==1: 
                location[i][0]+=1
                if location[i][0]>max[0]: location[i][0]=max[0]
            if move==2: 
                location[i][1]-=1
                if location[i][1]<0: location[i][1]=0
            if move==3: 
                location[i][1]+=1
                if location[i][1]>max[1]: location[i][1]=max[1]
            
            if location[i] == location[1-i]: return i
    return -1 


def tournament(pl):
    losses=[0 for p in pl]

    #多个玩家循环对战
    for i in range(len(pl)):
        for j in range(len(pl)):
            if i == j : continue

            #i,j比赛 0 i win 1 j win -2 ==平局
            winner=gridgame([pl[i],pl[j]])

            if winner==0:
                losses[j]+=2
            elif winner==1:
                losses[i]+=2
            elif winner==-1:
                losses[i]+=1
                losses[j]+=1
                pass

    #zip将列表组成元组，每个元素从每个列表取一个
    z=zip(losses,pl)
    z.sort()
    return z


#先机器人对抗，然后真人训练
class humanplayer:
  def evaluate(self,board):
    # Get my location and the location of other players
    me=tuple(board[0:2])
    others=[tuple(board[x:x+2]) for x in range(2,len(board)-1,2)]
    
    global chesssize
    # Display the board
    for i in range(chesssize):
      for j in range(chesssize):
        if (i,j)==me:
          print 'O',
        elif (i,j) in others:
          print 'X',
        else:
          print '.',
      print
      
    # Show moves, for reference
    print 'Your last move was %d' % board[len(board)-1]
    print ' 0'
    print '2 3'
    print ' 1'
    print 'Enter move: ',
    
    # Return whatever the user enters
    move=int(raw_input())
    return move


if __name__=="__main__":
    #运算从一个节点开始递归计算，每个节点都有 evaluate 方法，进行计算,方法先取得所有子节点求值，然后
    #传入节点功能函数中计算 参数作为列表一直随着树向下传递
    #一个树结构，代表了一个函数

    #et=exampletree()
    #et.display()

    #随机生成的程序

    #random1=makerandomtree(2)
    #print random1.evaluate([7,1])
    #random1.display()
    #hiddenset=buildhiddenset()
    #print scorefunction(random1,hiddenset)

    #rf=getrankfunction(buildhiddenset())
    #evolve(2,500,rf,mutationrate=0.2,breedingrate=0.1,pexp=0.7,pnew=0.1)

    #自动生成解决问题的程序，会生成大量不必要的程序，如果要得到更好的需要剪枝
    #利用编译器优化技术，或手动完成优化

    winner=evolve(5,100,tournament,maxgen=50)
    flag=gridgame([winner,humanplayer()])

    if flag==0:
        print 'yor are fail -^-'
    else:
        print 'you are win ^v^'


