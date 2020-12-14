
#-*-coding:utf8-*-

#很多问题最终都是优化问题
import time
import random
import math



#例1

#人和出发地点 -->New York
people = [('Seymour','BOS'),
          ('Franny','DAL'),
          ('Zooey','CAK'),
          ('Walt','MIA'),
          ('Buddy','ORD'),
          ('Les','OMA')]

# New York 的Laguardia机场
destination='LGA'

flights={}
for line in file('schedule.txt'):
  origin,dest,depart,arrive,price=line.strip().split(',')
  flights.setdefault((origin,dest),[])

  # Add details to the list of possible flights
  flights[(origin,dest)].append((depart,arrive,int(price)))

def getminutes(t):
  x=time.strptime(t,'%H:%M')
  return x[3]*60+x[4]


#目标使票价最低,在满足约束的情况下
#约束来源于需求

def printschedule(r):
  for d in range(len(r)/2):
    name=people[d][0]
    origin=people[d][1]
    out=flights[(origin,destination)][int(r[d])]
    ret=flights[(destination,origin)][int(r[d+1])]
    print '%10s%10s %5s-%5s $%3s %5s-%5s $%3s' % (name,origin,
                                                  out[0],out[1],out[2],
                                                  ret[0],ret[1],ret[2])


#设计成本函数度量方案好坏
#约束是一种不能违反的条件，或是一种违反了成本非常大的条件
#因此约束可以归于成本函数中，做罚函数
#多种因素我们应分清主次，给予重要的较大权值
#对不同事件合理量化，组合为一个成本函数

def schedulecost(sol):
  totalprice=0
  latestarrival=0
  earliestdep=24*60
  totalwait=0  


  for d in range(len(sol)/2):
    # Get the inbound and outbound flights
    origin=people[d][1]
    outbound=flights[(origin,destination)][int(sol[d])]
    returnf=flights[(destination,origin)][int(sol[d+1])]
    
    # Total price is the price of all outbound and return flights
    totalprice+=outbound[2]
    totalprice+=returnf[2]
    
    
    # Track the latest arrival and earliest departure
    if latestarrival<getminutes(outbound[1]): latestarrival=getminutes(outbound[1])
    if earliestdep>getminutes(returnf[0]): earliestdep=getminutes(returnf[0])
    
    totalwait+=getminutes(returnf[0])
    totalwait-=getminutes(outbound[1])
  # Every person must wait at the airport until the latest person arrives.
  # They also must arrive at the same time and wait for their flights.

  totalwait=totalwait+len(sol)/2*(latestarrival - earliestdep)
  # Does this solution require an extra day of car rental? That'll be $50!
  if latestarrival>earliestdep: totalprice+=50
  
  return totalprice+totalwait
  
  
def randomoptimize(domain,costf):
  best=999999999
  bestr=None
  for i in range(0,1000):
    # Create a random solution
    r=[float(random.randint(domain[i][0],domain[i][1])) 
       for i in range(len(domain))]
    
    # Get the cost
    cost=costf(r)
    
    # Compare it to the best one so far
    if cost<best:
      best=cost
      bestr=r 
  return r

def hillclimb(domain,costf):
  # Create a random solution
  sol=[random.randint(domain[i][0],domain[i][1])
      for i in range(len(domain))]
  # Main loop
  while 1:
    # Create list of neighboring solutions
    neighbors=[]
    
    for j in range(len(domain)):
      # One away in each direction
      if sol[j]>domain[j][0]:
        neighbors.append(sol[0:j]+[sol[j]+1]+sol[j+1:])
      if sol[j]<domain[j][1]:
        neighbors.append(sol[0:j]+[sol[j]-1]+sol[j+1:])

    # See what the best solution amongst the neighbors is
    current=costf(sol)
    best=current
    for j in range(len(neighbors)):
      cost=costf(neighbors[j])
      if cost<best:
        best=cost
        sol=neighbors[j]

    # If there's no improvement, then we've reached the top
    if best==current:
      break
  return sol



#退火，随机扰动并以一定概率(p=(-(h-l)/T)接受劣解
def annealingoptimize(domain,costf,T=10000.0,cool=0.95,step=1):
  # Initialize the values randomly
  vec=[float(random.randint(domain[i][0],domain[i][1])) 
       for i in range(len(domain))]
  
  while T>0.1:
    # Choose one of the indices
    i=random.randint(0,len(domain)-1)

    # Choose a direction to change it
    dir=random.randint(-step,step)

    # Create a new list with one of the values changed
    vecb=vec[:]
    vecb[i]+=dir

    #随机扰动并 
    #修正到范围内
    if vecb[i]<domain[i][0]: vecb[i]=domain[i][0]
    elif vecb[i]>domain[i][1]: vecb[i]=domain[i][1]

    # Calculate the current cost and the new cost
    ea=costf(vec)
    eb=costf(vecb)
    p=pow(math.e,(-eb-ea)/T)

    # Is it better, or does it make the probability
    # cutoff?
    if (eb<ea or random.random()<p):
      vec=vecb      

    # Decrease the temperature
    T=T*cool
  return vec

# mutprob 变异概率，elite 精英比例 
def geneticoptimize(domain,costf,popsize=50,step=1,mutprob=0.2,elite=0.2,maxiter=100):

    def mutate(vec):
        i=random.randint(0,len(domain)-1)
        if random.random()<0.5 and vec[i]>domain[i][0]:
            return vec[0:i]+[vec[i]-step]+vec[i+1:]
        elif vec[i]<domain[i][1]:
            return vec[0:i]+[vec[i]+step]+vec[i+1:]

    #随机选择一个位置将两个组合
    def crossover(r1,r2):
        i=random.randint(1,len(domain)-2)
        return r1[0:i]+r2[i:]


    #初始化种群
    pop=[]

    for i in range(popsize):
        vec=[random.randint(domain[i][0],domain[i][1]) for i in range(len(domain))]
        pop.append(vec)

    topelite=int(elite*popsize)

    cost=0

    for i in range(maxiter):
        scores=[(costf(v),v) for v in pop]
        scores.sort()


        #select elite (淘汰)
        ranked=[v for (s,v) in scores]
        pop=ranked[0:topelite]
        while len(pop)<popsize:
            if random.random()<mutprob:
                #选择一个变异
                c=random.randint(0,topelite)
                pop.append(mutate(ranked[c]))
            else:
                #选择两个交叉
                c1=random.randint(0,topelite)
                c2=random.randint(0,topelite)
                pop.append(crossover(ranked[c1],ranked[c2]))
            
        print scores[0][0]

    return scores[0][1]
    
if __name__=='__main__':
    #s=[1,4,3,2,7,3,6,3,2,4,5,3]

    domain=[(0,9)]*(len(people)*2)

    #s=hillclimb(domain,schedulecost)
    s=geneticoptimize(domain,schedulecost)
    printschedule(s)
    print schedulecost(s)
