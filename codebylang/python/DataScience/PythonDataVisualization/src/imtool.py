#!coding:utf8

from PIL import Image
from numpy import *

#im is array
def imresize(im,sz):
    pil_im=Image.fromarray(uint8(im))
    return array(pil_im.resize(sz))


#pca 
def pca(X):
    num_data,dim=X.shape

    #数据中心化
    mean_X=X.mean(axis=0)
    X=X- mean_X
    
    #通常使用SVD计算pca,维度很大时不使用SVD
    if dim>num_data:
        M=dot(X,X.T)
        #计算特征向量，投影到特征向量
        e,EV=linalg.eigh(M) 
        tmp=dot(X.T,EV).T 
        V=tmp[::-1]  #逆转
        S=sqrt(e)[::-1]#逆转特征值使降序

    else:
        U,S,V=linalg.svd(X)
        V=V[:num_data] # 仅返回前num_data dim

    return V,S,mean_X

