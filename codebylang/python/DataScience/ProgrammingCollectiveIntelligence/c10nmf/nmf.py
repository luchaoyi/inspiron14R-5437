#-*-coding:utf8-*-
from numpy import *
from pylab import *
import random





#nmf 呈现的关系易于解释，可以用于聚类
#例如:  单词×文档矩阵 (n*m)  = w(n*r)*h(r*m)  r为潜在特征,可以解释为某个主题
#则H阵为主题×文档，文档对某个主题值最大则可以判断属于某个主题.


#nmf寻找复杂数据下隐藏的潜在特征，将数据用潜在特征解释 W是记录与潜在特征关系 H是潜在特征与表明特征关系

#两个矩阵差异值
#V~WH W>0 V>0 V近似分解为两个所有元素非负的矩阵-->优化问题
#min J=1/2||V-WH||  st.W>0,V>0
def difcost(a,b):
    dif=0
    for i in range(shape(a)[0]):
        for j in range(shape(a)[1]):
            dif+=pow(a[i,j]-b[i,j],2)

    return dif




def factorize(v,r=10,iter=50):
    m,n=shape(v)
    cost=[[],[]]

    #v=w*h (m*n=m*r * r*n)
    # m*r

    w=matrix([[random.random() for j in range(r)] for i in range(m)])
    #r*n
    h=matrix([[random.random() for j in range(n)] for i in range(r)]) 

    for i in range(iter):
        wh=w*h
        cost[0].append(i)
        cost[1].append(difcost(v,wh))
        if cost==0:break
        hn=(transpose(w)*v)#w^T*v
        hd=(transpose(w)*w*h)#w^T*w*h
        #对应元素运算，非矩阵运算
        h=matrix(array(h)*array(hn)/array(hd))

        wn=(v*transpose(h))
        wd=(w*h*transpose(h))

        w=matrix(array(w)*array(wn)/array(wd))

    plot(cost[0],cost[1])
    show()
    return w,h
        



if __name__=='__main__':
    
    m1=matrix([[1,2,3],[4,5,6]])
    m2=matrix([[1,2],[3,4],[5,6]])

    w,h=factorize(m1*m2,3,100)
    print w*h

        


