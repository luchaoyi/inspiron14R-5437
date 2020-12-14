#!coding:utf8

import random
from numpy import *
from copy import deepcopy


#Hesse矩阵
def H(f,x,delta=0.0001):
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


#梯度
#x is a array
def gf(f,x,delta=0.0001):
    n=len(x)
    gx=[0]*n
    for i in range(n):
        xbar=deepcopy(x)
        xbar[i]=xbar[i]+delta
        gx[i]=(f(xbar)-f(x))/delta
    return gx


#用割线法一维搜索
#用割线法搜索xk+1=xk+la*pk中的步长la
def secant(f,xk,pk,thres=0.00001):
    la0=random.random()*random.randint(0,2)+0.5
    la1=la0+random.randint(0,2)+1
    while abs(dfla(f,xk,pk,la1))>thres:
        la2=la1-(la1-la0)*dfla(f,xk,pk,la1)/(dfla(f,xk,pk,la1)-dfla(f,xk,pk,la0)+thres)#+对thres避免div 0
        la0=la1
        la1=la2
    return la1


def split_618(f,xk,pk,l,h,thres=0.00001):
    #_618影响搜索精度

    _618=(5**0.5-1.0)/2
    la1=l+(h-l)*_618
    la2=l+(h-la1)

    while h-l>thres:
        x1=xk+la1*pk
        x2=xk+la2*pk 
        if(f(x1)>=f(x2)):
            h=la1 
            la1=la2 
            la2=l+(h-la1)
        else:
            l=la2
            la2=la1
            la1=l+(h-la2)
            
    return h/2+l/2

#连分式


def dfla(f,xk,pk,la,delta=0.0001):
    xka=xk+(la+delta)*pk
    xkb=xk+la*pk
    return (f(xka)-f(xkb))/delta
