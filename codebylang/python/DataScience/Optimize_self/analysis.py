#!coding:utf8

#Bug point:
#matlab index start 1 ;python index start 0
#matlab 1:3=1,2,3;python 1:3=1,2 without 3
#python 1/2=0 1.0/2=1.0/2.0=0.5
#注意numpy的array和mat如果生成为整数类型，则存储浮点类型会自动取整


from copy import deepcopy
from numpy import *
from random import *

def gradient(f,gf,x0,thres=0.0001):
    while True:
        p=-1*array(gf(f,x0))
        if linalg.norm(p,2)<=thres:
            return x0
        la=secant(f,x0,p)
        x0=x0+la*p
        #print f(x0)

#梯度下降z型收敛，接近最优点收敛缓慢，改进2次梯度下降xk->xk+1->xk+2,使用一次xk+2-xk
#实验证明改进梯度下降效果非常明显,梯度下降在最优点附近收敛非常慢
def partan(f,gf,x0,thres=0.0001):
    while True:
        x=[]
        for i in range(2):
            p=-1*array(gf(f,x0))
            if linalg.norm(p,2)<=thres:
                return x0 
            if i==0:
                x.append(x0)
            la=secant(f,x0,p)
            x0=x0+la*p

            if i==1:
                x.append(x0)

        p=x[1]-x[0]
        la0=random()*randint(0,2)
        la1=la0+randint(0,2)
        x0=x0+la*p
        #print f(x0)

#附加动量的梯度下降,下降时附加上一次移动的动量
#partan法改进更明显
def mgradient(f,gf,x0,thres=0.0001):
    x0=array(x0)
    x1=x0
    while True:
        p=-1*array(gf(f,x0))
        if linalg.norm(p,2)<=thres:
            return x0
        la=secant(f,x0,p)
        xpre=x0
        x0=x0+la*p+0.25*(x0-xpre)
        #print f(x0)

#xk+1=xk-la*H^-1*gk
def newton(f,gf,x0,thres=0.0001):
    while True:
        #梯度
        p=mat(gf(f,x0))
        if linalg.norm(p,2)<=thres:
            return x0

        p=-p*(linalg.pinv(Hesse(f,x0)))
        p=p.A[0]
        la=secant(f,x0,p)
        xpre=x0 
        x0=x0+la*p

        #增加一个判断条件，避免梯度一直降不到低于thres.
        if abs(f(xpre)-f(x0))<thres:
            return x0

#牛顿方法是二次近似后求f'(x)=0导出的，因此xk接近x*近似效果比较理想.
#改进方法:初始采用梯度法，接近时采用牛顿法.
#改进方法数值稳定性更高.
def gradient_newton(f,gf,x0,thres=0.0001):
    #梯度法粗搜，thres设置大一点
    x0=mgradient(f,gf,x0,1.0)
    x0=newton(f,gf,x0,thres)
    return x0


#二次凸函数，沿一组Q共轭的非零向量迭代，最终g(n+1)与p1,..pn都正交，因此g(n+1)=0，所以n次收敛.
#二次凸函数 f(x)=1/2*x.TQx+bx+c。
#非二次函数共轭梯度法用hesse矩阵代替Q二次近似
#沿n个方向迭代n次后可以重新开始算法减少累积误差.
#共轭梯度法，使用梯度信息构造共轭向量
def conjugate_gradient(f,gf,x0,thres=0.0001):
    n=len(x0)
    g0=gf(f,x0)
    if linalg.norm(g0,2)<thres:
        return x0

    while True:
        #迭代n次，重新开始,减少累积误差
        alpha=0
        z=-array(g0)
        for i in range(n):
            la=secant(f,x0,z)
            x1=x0+la*z
            g1=gf(f,x1)
            if linalg.norm(g1,2)<thres:
                return x1
            alpha=(mat(g1)*(mat(g1)-mat(g0)).T)[0,0]/linalg.norm(g0,2)**2

            #zk+1=-gk+1 + alpha*zk
            z=-array(g1)+alpha*z
            x0=x1 
            g0=g1
            #print x1


#拟牛顿法，在迭代中产生Hk来逼近H^-1，避免Hesse矩阵求逆，简化计算量
#Hk+1=Hk+deltaHk
#需要满足拟牛顿性(Hk+deltaHk)*deltagk=deltaxk
#不同的拟牛顿法构造Hk方法不同
#DFP法产生的z1,...zn是共轭的因此DFP也是一种共轭法,对于二次凸函数n步收敛
#迭代n次后重新计算，降低累积误差


def DFP(x1,x0,g1,g0,H,thres=0.00001):
    #delta_x,delta_g都为列向量
    delta_x=mat(x1-x0).T
    delta_g=mat(array(g1)-array(g0)).T

    r=H*delta_g 
    H=H+delta_x*delta_x.T/(delta_x.T*delta_g+thres)-r*r.T/(delta_g.T*H*delta_g+thres) 
    return H

#BFGS产生的HK数值稳定性最好
def BFGS(x1,x0,g1,g0,H,thres=0.00001):
    delta_x=mat(x1-x0).T
    delta_g=mat(array(g1)-array(g0)).T
    beta=1+delta_g.T*H*delta_g/(delta_x.T*delta_g+thres)
    beta=beta[0,0]
    H=H+(beta*delta_x*delta_x.T-H*delta_g*delta_x.T-delta_x*delta_g.T*H)/(delta_x.T*delta_g+thres)
    return H


#HK是产生HK的方法
def Quasi_Newton(f,gf,x0,HK=BFGS,thres=0.0001):
    n=len(x0)
    x0=array(x0)

    g0=gf(f,x0)
    if linalg.norm(g0,2)<thres:
        return x0

    while True:
        #迭代n次，重新开始,减少累积误差
        H=mat(diag([1.0]*n))
        z=((-H*mat(g0).T).T.A)[0]
        for i in range(n):
            la=secant(f,x0,z)
            x1=x0+la*z
            g1=gf(f,x1)
            if linalg.norm(g1,2)<thres:
                return x1

            H=HK(x1,x0,g1,g0,H)

            #print H
            #print "---"
            #print linalg.pinv(Hesse(f,x1))

            x0=x1 
            g0=g1



def Hesse(f,x,delta=0.0001):
    n=len(x)
    Hmat=mat(zeros([n,n]))
    for i in range(n):
        for j in range(i,n):
            xbar=deepcopy(x)
            xbar[j]=xbar[j]+delta 
            #gf(x)[i]表示f(x)对x[i]的偏导函数
            Hmat[j,i]=(gf(f,xbar)[i]-gf(f,x)[i])/delta
            Hmat[i,j]=Hmat[j,i]
    return Hmat


#x is a array
def gf(f,x,delta=0.0001):
    n=len(x)
    gx=[0]*n
    for i in range(n):
        xbar=deepcopy(x)
        xbar[i]=xbar[i]+delta
        gx[i]=(f(xbar)-f(x))/delta
    return gx

#用割线法一维搜索,步长la对算法影响较大，所以搜索步长.
def secant(f,xk,pk,thres=0.00001):
    la0=random()*randint(0,2)+0.5
    la1=la0+randint(0,2)+1
    while abs(dfla(f,xk,pk,la1))>thres:
        la2=la1-(la1-la0)*dfla(f,xk,pk,la1)/(dfla(f,xk,pk,la1)-dfla(f,xk,pk,la0)+thres)#+对thres避免div 0
        la0=la1
        la1=la2
    return la1

def dfla(f,xk,pk,la,delta=0.0001):
    xka=xk+(la+delta)*pk
    xkb=xk+la*pk
    return (f(xka)-f(xkb))/delta


if __name__=="__main__":
    def tf0(x):
        return (x[0]-4)**2+(x[1]+2)**2+1
    def tf1(x):
        return 3*x[0]**2+x[1]**2-2*x[0]*x[1]+4*x[0]+3*x[1]+x[2]**2


    #print H(tf0,[0,0])
    #print linalg.pinv(H(tf0,[0,0]))
    #print "----"

    x=[100.0]*2
    x=mgradient(tf0,gf,x)
    print x,tf0(x)
    print "-------"
    
    x=[100.0]*2
    x=partan(tf0,gf,x)
    print x,tf0(x)
    print "-------"

    x=[10000000.0]*2
    x=newton(tf0,gf,x)
    print x,tf0(x)
    print "-------"

    x=[10000000.0]*2
    x=gradient_newton(tf0,gf,x)
    print x,tf0(x)
    print "-------"

    x=[100000.0]*2
    x=conjugate_gradient(tf0,gf,x)
    print x,tf0(x)
    print "-------"

    x=[100000.0]*2
    x=Quasi_Newton(tf0,gf,x,DFP)
    print x,tf0(x)
    print "-------"

    x=[100000.0]*2
    x=Quasi_Newton(tf0,gf,x,BFGS)
    print x,tf0(x)
    print "-------"

    x=[100.0]*3
    x=mgradient(tf1,gf,x)
    print x,tf1(x)
    print "-------"

    x=[100.0]*3
    x=partan(tf1,gf,x)
    print x,tf1(x)
    print "-------"

    x=[100000.0]*3
    x=newton(tf1,gf,x)
    print x,tf1(x)
    print "-------"

    x=[100000.0]*3
    x=gradient_newton(tf1,gf,x)
    print x,tf1(x)
    print "-------"

    x=[100000.0]*3
    x=conjugate_gradient(tf1,gf,x)
    print x,tf1(x)
    print "-------"

    x=[100000.0]*3
    x=Quasi_Newton(tf1,gf,x,DFP)
    print x,tf1(x)
    print "-------"

    x=[100000.0]*3
    x=Quasi_Newton(tf1,gf,x,BFGS)
    print x,tf1(x)
    print "-------"
