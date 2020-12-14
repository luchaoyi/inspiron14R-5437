# -*-coding: utf-8 -*-
import random
import numpy

from bayes import *
from tool import *

#数据抽样
#DataMat 训练数据
#listClasses 训练数据标签
def GenerateData(DataMat,listClasses):

    m=len(DataMat)
    #print m

    BaggingData=[]
    BagginglistClasses=[]

    for i in range(m):
        j=random.randint(0,m-1)
        BaggingData.append(DataMat[j])
        BagginglistClasses.append(listClasses[j])

    return BaggingData,BagginglistClasses

#分类器训练
def BagTrain(bag_count,trainMat,listClasses):
    P0v_1v_Ab=[]
    Error=[]
    for i in range(bag_count):
        trainMat_i,listClasses_i=GenerateData(trainMat,listClasses) #生成数据
        #trainMat_i=imgCompress(trainMat_i)
        p0V,p1V,pAb = trainNB0(array(trainMat_i),array(listClasses_i))#分类器训练
        P0v_1v_Ab.append([p0V,p1V,pAb])
    return P0v_1v_Ab
    

def ClassifyVote(Result):
    n1=0
    n0=0

    for i in range(len(Result)):
        if Result[i] == 1:
            n1+=1
        else:
            n0+=1
            
    if  n1>n0:
        return 1
    else:
        return 0

def ClassResult(AllClassList):
	#M*K M个样品K个分类，K个分类器
    M,K = numpy.shape(AllClassList)

    CR=[]
    for i in range(M):
        Ci=ClassifyVote(AllClassList[i])
        CR.append(Ci)

    return CR

#预测待预测样本分类
def BagPredict(bag_count,trainMat,listClasses,predictMat):
   	#训练分类器
    P0v_1v_Ab=BagTrain(bag_count,trainMat,listClasses)
    AllClassList=[]
    
    #K*M
    for i in range(bag_count):
        PredictClassList=[]
        P0V,p1V,pAb=P0v_1v_Ab[i]

        for j in range(len(predictMat)):
            thisDoc = predictMat[j]
            PredictClass=classifyNB(thisDoc,P0V,p1V,pAb)
            PredictClassList.append(PredictClass)
            AllClassList.append(PredictClassList)
    #print AllClassList
    AllClassList=numpy.array(AllClassList).T
    CR=ClassResult(AllClassList)
    return CR





        







