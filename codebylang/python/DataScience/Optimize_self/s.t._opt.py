#!coding:utf8

from numpy import *
from copy import deepcopy
from mathtools import *

#x0 is 初始可行点
def rosen_gradient(f,x0,A,b,E,e,gf=gf,thres0=0.001,thres1=0.000001):
    n=len(x0)
    x0=mat(x0).T
    mE=len(E)

    while True:
        I=(A*x0-b).A1
        #A*x-b=0
        #数组过滤
        S=array([abs(Ii-0.0)<thres1 for Ii in I])
        A1=A[S]
        A2=A[-S]
        b2=b[-S]
        mA1=len(A1)

        if mE !=0:
            Aq=append(A1,E).resize([mA1+mE,n])
            mAq=mA1+mE 
        else:
            Aq=A1
            mAq=mA1

        g=mat(gf(f,x0.A1)).T
        flag=True 

#        print x0
#        print Aq

        while flag:
            d=-g 
            if mAq!=0:
                P=mat(diag(ones(n)))-(Aq.T*linalg.pinv(Aq*Aq.T)*Aq)
                d=P*d
		#else: d=d=-g
	    #||d||2=0

            #这里thres设置太小会使算法不能进入这个分支，而不能收敛
            #投影梯度粒度可以放粗一点，但最优点在内部时精度度不足
            #thres0粗精度，处于边界时用此精度，thres1细精度处于内部时使用
    	    if linalg.norm(d,2)<thres0:
    	        if mAq==0: 
                    #if mAq=0处于内部时，精度更高一点
                    if linalg.norm(d,2)<thres1:
                        return x0.A1  
	        else:
                    beta=linalg.pinv(Aq*Aq.T)*Aq*g
	            u=beta[0:mA1]
    	            #all>=0
                    #KT点
                    u=[ui for ui in u.A1]
                    if min(u)>=0:
                        return x0.A1
		        #不是KT点
	            else:
                        j=u.index(min(u))
                        #去除A[j]
                        Aq[j:mAq-1]=Aq[j+1:mAq]
                        mAq=mAq-1
    	    #||d||!=0
	    else:
                b_bar=b2-A2*x0
                d_bar=A2*d
                #all d_bar[i]>=0
                if min(d_bar.A1)>=0:
                    #la的max is +INF,没有上界
                    #0<=la<=+INF
                    la=max(0,secant(f,x0.A1,d.A1))
                else:
                    la_max=min([b_bar[i,0]/d_bar[i,0] for i in range(len(d_bar)) if d_bar[i,0]<0])
                    la=split_618(f,x0.A1,d.A1,0,la_max)
                x0=x0+la*d
                flag=False
            


def Lag():
    return 0


#二次规划，采用起作用集约束方法
def QP():
    return 0


#非二次规划用泰勒展开近似转化为近似QP,不断迭代求解
def SQP():
    return 0





if __name__=="__main__":
    def tf(x):
        return 2*x[0]**2+x[1]**2-2*x[0]*x[1]+3*x[0]-8*x[1]+2
    x=[0.0,0.0]
    A=mat([[-1.0,1.0],[-3.0,-5.0]])
    b=mat([-4.0,-8.0]).T
    x=rosen_gradient(tf,x,A,b,[],[],gf)
    print x,tf(x)







