# -*-coding: utf-8 -*-
from numpy import *
from numpy import linalg as la

#SVD奇异值分解
def imgCompress(myMat,threshold):
    U,Sigma,VT = la.svd(myMat)
    #print U
    #print "----------------------"
    #print Sigma
    #print "----------------------"
    #print VT

    numSV=svdSigmaSelect(Sigma,threshold)
    SigRecon = mat(zeros((numSV, numSV)))
    for k in range(numSV):#construct diagonal matrix from vector
        SigRecon[k,k] = Sigma[k]
    reconMat = U[:,:numSV]*SigRecon*VT[:numSV,:]
    return reconMat

#此处可以讨论SVD逼近程度(信息损失程度),对精度的影响
def svdSigmaSelect(Sigma,threshold):
    S_sigma=sum(Sigma)
    A_sigma=0

    i=0

    while (float(A_sigma)/float(S_sigma))<threshold:
        A_sigma+=Sigma[i]
        i+=1

    #print "SVD select Sigma number",i
    return i
    
#计算分类误差率
def error(x,y):
    #print x
    #print y
    m=len(x)
    sum=0
    for i in range(m):
        if x[i] != y[i]:
            sum+=1
    return float(sum)/m

