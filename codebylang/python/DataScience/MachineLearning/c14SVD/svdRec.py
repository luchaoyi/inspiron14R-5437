# -*-coding: utf-8 -*-
# -*-coding:utf-8 -*- 
#!/usr/bin/python2.7 

from numpy import *
from numpy import linalg as la

"""
推荐引擎思想：搜索引擎是基于用户检索关键字计算相似度排名
而推荐引擎是基于用户的行为特征计算相似度排名


基于内容的推荐：
当无法获取用户评价信息时，则将推荐看作搜索问题
构造物品的特征计算相似度
"""


# 1/1+d
# while d = 0 sim = 1 
def ecludeSim(inA,inB):
    return 1.0/(1.0+la.norm(inA-inB))

def cosSim(inA,inB):
    AB = float(inA.T*inB)
    denom = la.norm(inA)*la.norm(inB)

    #cos@ = [-1,1] ->0.5[-1,1]+0.5 ->[0,1]
    return 0.5+0.5*(AB/denom)

def pearsSim(inA,inB):
    if len(inA)<3: return 1.0
    return 0.5+0.5*corrcoef(inA,inB,rowvar=0)[0][1]



#user:user number
#item:item number
#predict user rating item 
def standEst(dataMat,user,simMeas,item):

    n=shape(dataMat)[1]#m*n item total number

    simTotal = 0.0;ratSimTotal = 0.0
    for j in range(n):
        userRating = dataMat[user,j]

        #user no rating 
        if userRating == 0:continue
        
        # item >0 and j>0  return rating item j user ID
        #find rating item ,j user
        overLap = nonzero(logical_and(dataMat[:,item].A>0,dataMat[:,j].A>0))[0]

        #no user rating no one contribute to information
        if len(overLap) == 0: similarity = 0
        #use rating information calculate
        else:
            similarity = simMeas(dataMat[overLap,item],dataMat[overLap,j],simMeas)
 
 
        
        #compare item  no rating with user rating predict rating
        #item similarity is a weight
        #w1*r1+w2*r2+.../w1+w2+...
        #weight ->[0,1]
        simTotal += similarity
        ratSimTotal += similarity*userRating
    if simTotal == 0: return 0
    else: return ratSimTotal/simTotal

def svdEst(dataMat,user,simMeas,item):
    n = shape(dataMat)[1]

    simTotal = 0.0;ratSimTotal = 0.0

    
    #m*n -->U(m*n)*E(n*n)*VT(n*n)

    U,Sigma,VT=la.svd(dataMat)
    
    #select 4 Singular value
    #m*4
    Sig4 = mat(eye(4)*Sigma[:,:4])
    #use matrix U map col --> feature space filter col feature continue low

    #dataMat.T(n*m)*U(m,4) -->n*4 n item ,4 people 
    
    
  
    xformedItems = dataMat.T*U[:,:4]*Sig4.I

    print xformedItems
	
    for j in range(n):
        userRating = dataMat[user,j] #用户user对物品j的评分
		
		#！=0 的表示此user已评分，可以用来计算相似度
		
        if userRating == 0 or j == item :continue
        
        #计算物品j与待预测物品item相似度
        
        #U=[u1,u2,..] 列向量构成D的列空间的正交基即将D列向量映射打到ui张成的空间
        #V则是行空间映射
		#协同过滤 基于物品：是计算其它物V品与此物品相似度 基于都已评分的计算相似度
		#										    书籍
		
		#									       [
		#SVD分解后只是在低维空间计算相似度       用户     ]  D（m*n） = m*n n*n n*n --> m*k(U) k*k k*n(V.T)     
		#		U（m*k）将书籍（纵向）映射到k维（低维）空间       n*m*m*k*Sigma =n*k  低维物品空间 n个书籍维度变低 
		
        similarity = simMeas(xformedItems[item,:].T,xformedItems[j:,].T)

        simTotal +=similarity
        ratSimTotal +=similarity*userRating


    if simTotal == 0:return 0
    else: return ratSimTotal/simTotal


#find user no rating item , predict rating sorted return 
def recommend(dataMat,user,N=3,simMeas=cosSim,estMethod=standEst):

    #1 find user no rating 
    usernoRatingitem = nonzero(dataMat[user,:].A<1)[1]

    if len(usernoRatingitem) == 0:
        return "all item rating"

    ItemRatingpredict={}

    for item in usernoRatingitem:
        ItemRatingpredict[item] = standEst(dataMat,usr,simMeas,item)


    return sorted(ItemRatingpredict.iteritems(),key=lambda p:p[1],reverse=true)

    



