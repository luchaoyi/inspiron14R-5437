#!coding:utf8

#Bug point:
#matlab index start 1 ;python index start 0
#matlab 1:3=1,2,3;python 1:3=1,2 without 3
#python 1/2=0 1.0/2=1.0/2.0=0.5
#[0,0,...0]*n,n个列表引用的是同一块内存位置，因此会出现bug
#python非基本元素一定注意浅复制bug
#d=[[0 for i in range(n)] for j in range(n)]


from numpy import *
from copy import deepcopy
from mathtools import *

#探测移动x->y,寻找可能下降的方向,f(y)更小.如果探测失败则收缩探测步长（可以一维搜索步长)
#模式移动以y为起点沿y-x这个可能下降的方向移动z=y+beta(y-x)
#f(z)更小则模式移动成功，以z为新起点，迭代。若f(z)>f(y)则模式移动失败，以y为新起点
def hooke_jeeves(f,x,thres=0.0001,beta=1,alpha=0.75,delta=20):
    n=len(x)
    y=deepcopy(x)

    while delta>thres:
        #沿每个方向搜索一遍
        for i in range(n):
            xp=y[0:n]
            xp[i]=xp[i]+delta 

            fy=f(y)
            if f(xp)<fy:
                y=xp
            else:
                xn=y[0:n]
                xn[i]=xn[i] - delta
                if f(xn)<fy:
                    y=xn
        #e1,e2,en探测一轮,成功
        fy=f(y)
        if fy<f(x):
            z=[y[i]+beta*(y[i]-x[i]) for i in range(n)]
            #模式移动成功z起点，失败y起点
            if f(z)<fy:
                x=z
            else:
                #改进beta步长移动失败不立即回退，尝试0.4,0.6
                z_04=[y[i]+0.4*(y[i]-x[i]) for i in range(n)]
                z_06=[y[i]+0.6*(y[i]-x[i]) for i in range(n)]
                if f(z_04)<fy:
                    x=z_04
                elif f(z_06)<fy:
                    x=z_06
                else:
                    x=y
        #探测失败缩小步长
        else:
            delta=alpha*delta
    return x

#A可逆则A=QR，Q是对A=(a1,a2...an),n个线性无关列向量的单位正交化.
#alpha伸长步长，beta收缩步长.
def rosenbrock(f,x,thres=0.0001,alpha=2,beta=0.5):
    n=len(x)
    delta=[1.0]*n
    d=diag(ones(n))
    lam=zeros(n) #记录沿每个方向移动距离之和,则si=lami*diag

    x0=array(x)
    xi=deepcopy(x0)
    z0=deepcopy(x0)
    zi=deepcopy(x0)

    #穷尽步长和方向的潜力
    #方向潜力下降构造新方向
    #方向完全没有潜力(接近最优值了)，则穷尽步长潜力（缩小步长，精细搜索)

    while True:
        #沿n个方向探测.
        for i in range(n):
            if f(zi+delta[i]*d[i])<f(z0):
                zi=zi+delta[i]*d[i]
                lam[i]=lam[i]+delta[i]
                delta[i]=alpha*delta[i]
            else:
                delta[i]=-beta*delta[i]

        #n个方向试探至少一次成功,继续沿n个方向试探
        if f(zi)<f(z0):
            z0=zi
            continue

        #最近一轮n个方向试探失败
        else:
            #最近一轮失败,但多轮中有一轮成功
            if f(zi)<f(x0):
                xi=zi
                if linalg.norm(xi-x0)<thres:
                    return xi

                #构造新方向
                s=zeros([n,n])
                for i in range(n):
                    s[i]=lam[i]*d[i]
                Q,R=linalg.qr(s.T)
                d=Q.T

                lam=zeros(n)
                delta=[1.0]*n
                x0=xi

            #最近一轮失败,且多轮中没有一轮成功
            else:
                #步长已经很小,没有继续探测的潜力，结束.
                #否则继续沿此n个方向探测(步长会继续缩小)
                if linalg.norm(delta)<thres:
                    return x0
                else:
                    z0=zi
                    #continue
                    
 
 
#powell产生共轭向量组思想：从不同点x1,x2出发,沿一组共轭方向z1,z2,...zn直线搜索,得到极小点x1*,x2*,则p=x1*-x2*与z1,...zn共轭 
#powell算法从(e1,...en)搜索依据上述思想迭代n次产生一组共轭向量组(z1,...zn)。
#在定理9.4假设下,B=(z1,z2,...zn),z1,...z2为共轭时det(B)最大，新产生方向是否能使det(B)增大是判断条件的思想.
def conjugate_powell(f,x0,thres=0.0001): 
    #不同点从同一个共轭方向搜索极小点,点的差向量是新的共轭方向
    n=len(x)
    z=diag([1.0]*n)

    x0=array(x0)
    x1=deepcopy(x0)
    x2=deepcopy(x1)

    while True:
        #沿搜索方向走n次产生一个共轭方向

        delta_fm=-inf
        for i in range(n):
            #x1->...->xn
            la=secant(f,x1,z[i])
            x2=x1+la*z[i]
            if f(x1)-f(x2)>delta_fm:
                delta_fm=f(x1)-f(x2)
                im=i
            x1=x2 

        if linalg.norm(x2-x0,2)<thres:
            return x1

             
        if f(x0)-2*f(x2)+f(2*x2-x0)<2*delta_fm:
            z[im:n-1]=z[im+1:n]
            z[n-1]=x2-x0 
            la=secant(f,x1,z[n-1])
            x1=x1+la*z[n-1]
            #x[n-1]最后沿新产生方向z[n-1]走一步x[n] 
            #上一轮x[n] is 新一轮 x[0]->...-> x[n-2]->z[n-1]->x[n-1] 
            #新一轮x[n-1]是沿z[n-1]搜到
            #上一轮x[n]is新一轮x[0]沿z[n-1]搜到
            #不同点同一方向

        x0=deepcopy(x1) 

                    
if __name__=="__main__":
    def tf0(x):
        return 3*x[0]**2+x[1]**2-2*x[0]*x[1]+4*x[0]+3*x[1]+x[2]**2

    #print tf([-1.75,-3.25])

    x=[100]*3
    x=hooke_jeeves(tf0,x,delta=50) 
    print x,tf0(x)

    #搜索步长与距离极值点距离有关
    x=[10000]*3
    x=rosenbrock(tf0,x) 
    print x,tf0(x)

    x=[10]*3
    x=conjugate_powell(tf0,x) 
    print x,tf0(x)
    
