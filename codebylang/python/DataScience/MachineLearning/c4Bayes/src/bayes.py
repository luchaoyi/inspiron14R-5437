# -*-coding: utf-8 -*-

from numpy import *
import os
import chardet
import copy

#训练
def trainNB0(trainMatrix,trainCategory):

    #print trainMatrix
    #print trainCategory
    numTrainDocs = len(trainMatrix)
    numWords = len(trainMatrix[0])
    #==1    
    pAbusive = sum(trainCategory)/float(numTrainDocs)
    #print pAbusive
    p0Num = ones(numWords); p1Num = ones(numWords)      #change to ones() 
    p0Denom = 2.0; p1Denom = 2.0                        #change to 2.0
    for i in range(numTrainDocs):
        if trainCategory[i] == 1:
            p1Num += trainMatrix[i]
            p1Denom += sum(trainMatrix[i])
        else:
            p0Num += trainMatrix[i]
            p0Denom += sum(trainMatrix[i])

    
    #print p1Num/p1Denom
    p1Vect = log(p1Num/p1Denom)          #change to log()
    p0Vect = log(p0Num/p0Denom)          #change to log()
    return p0Vect,p1Vect,pAbusive

#分类
def classifyNB(vec2Classify, p0Vec, p1Vec, pClass1):
    p1 = sum(vec2Classify * p1Vec) + log(pClass1)    #element-wise mult
    p0 = sum(vec2Classify * p0Vec) + log(1.0 - pClass1)
    if p1 > p0:
        return 1
    else: 
        return 0
    
 
        
        
        
        


 
        



