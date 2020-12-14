#coding:utf8
import random

#LC算法虽然由于空间复杂度不够理想已经很少被单独使用，但是由于其在元素数量较少时表现非常优秀，因此常被用于弥补LogLog Counting在元素较少时误差较大的缺陷
def LC():
    import math
    m=5000
    S=[random.randint(0,m-1) for i in range(400)]
    bitmap=[0]*m #这里用list模拟bit
    
    for e in S:
        #认定hash是均匀的则k服从均匀分布
        #则p(k==j)=1/m,here m=100
        k=hash(e)
        bitmap[k]=1 #对应位图置1
    
    #print sum(bitmap)
    u=m-sum(bitmap) #不为0的个数为u
    if u==0:
        print "桶满了!" #如果m比n小太多，则很有可能所有桶都被哈希到了，此时u的值为0，LC的估计公式就不起作用了
    else:
        print -m*math.log(float(u)/m)
        print len(set(S))
    
    
LC()
    
    
    
    
    
