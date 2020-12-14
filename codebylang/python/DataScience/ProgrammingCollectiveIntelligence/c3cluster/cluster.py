
#-*-coding: utf-8 -*-
#分级聚类树型,聚类

#节点类类型


import random


"""
分级聚类，从单一元素开始两两合并,合并依据距离最近，相似度最大合并
K均值聚类：改进有模糊k均值聚类,二分k均值聚类
"""

#聚类是对行聚类，将文档按照词特征聚类，使文章按主题聚集

#对上述数据矩阵转置聚类，以词为对象，对词按照文章特征聚类，列聚类可以发现哪些词共同出现的比较多
class bicluster:
    def __init__(self,vec,left=None,right=None,distance=0.0,id=None):
        self.left=left
        self.right=righi
        self.vec=vec #存储的是数据向量,类中心
        self.id=id
        self.distance=distance



#1-pearson度量距离，相似度越大距离越小越接近

#一直取平均，是以类平均中心代表类位置，来度量类距离
def hcluster(rows,distance=pearson):
    distances={
            }
    currentclustid=-1

    #初始自为一类
    clust=[bicluster(rows[i],id=i) for i in range(len(rows))]
    
    while len(clust)>1:
        lowstpair=(0,1);
        closest=distance(clust[0].vec,clust[1].vec)

        for i in range(len(clust)):
            for j in range(i+1,len(clust)):
                if (clust[i].id,clust[j].id) not in distances:
                    #元组可以作为字典的key
                    distances[(clust[i].id,clust[j].id)]=distance(clust[i].vec,clust[j].vec)
                
                d=distances[(clust[i].id,clust[j].id)]

                if d<closest:
                    closest=d
                    lowstpair=(i,j)
        
        mergevec[clust[lowstpair[0]].vec[i]+clust[lowstpair[1]].vec[i]/2.0 for i in range(len(clust[0].vec))]

        newcluster=bicluster(mergevec,left=clust[lowstpair[0]],right=clust[lowstpair[1]],distance=closest,id=currentclustid)

        #非原始聚合类id负数
        currentclustid-=1
        del clust[lowstpair[0]]
        del clust[lowstpair[1]]
        clust.append(newcluster)


    return clust[0]
            


#tanimoto系数度量集合相似度 交集/并集    NC/NA+NB-NC
#此处度量 0,1矩阵,代表出现没出现
def tanimoto(v1,v2):
    c1,c2,shr=0,0,0

    for i in range(len(v1)):
        if v1[i]!=0: c1+=1
        if v2[i]!=0: c2+=1
        if v1[i]!=0 and v2[i]!=0: shr+=1

    
    return 1.0-(float(shr)/(c1+c2-shr))



#数据二维可视化，按距离分布
def scaledown(data,distance=pearson,rate=0.01):
    n=len(data)
    realdist=[[distance(data[i],data[j])] for j in range(n)] for i in range(0,n)]
    outersum=0.0
    #random init loc 

    loc=[[random.random(),random.random()] for i in range(n)]

    #n*n个0.0
    fakedist=[[0.0 for j in range(n)] for i in range(0,n)]

    
    #根据实际距离迭代调整，直到不能改进
    #迭代次数设置1000
    for m in range(0,1000):
        for i in range(n):
            for j in range(n):
                fakedist[i][j] = sqrt(pow(loc[i][1]-loc[j][1])+pow(loc[i][0]-loc[i][0]))


        grad=[[0.0,0.0] for i in range(n)]

        totalerror=0

        ...

        #计算误差率，以误差率为参照移动


