#!/usr/bin/python2.7 



from math import log
from numpy import *

#use all sample generate a vocablist
def createVocabList(dataSet):

    vocabSet =set([])

    for document in dataSet:
        vocabSet = vocabSet | set(document)

    return list(vocabSet)


def setOfWords2vec(vocablist,inputSet):
    returnVec = [0]*len(vocablist)

    for word in inputSet:
        if word in vocablist:
            returnVec[vocablist.index(word)] = 1
        else: 
            print "%s is not in vocablist" %word
    return returnVec


#m*n m sample n feature
def trainNB0(trainMartix,trainCategory):
	numTrainDocs = len(trainMartix)#m
	numWords = len(trainMartix[0])#n

	p1 = sum(trainMartix)/float(numTrainDocs)

	
	#statistics feature 
	#p0Num=zeros(numWords)
	#p1Num=zeros(numWords)
	p0Num=ones(numWords)
	p1Num=ones(numWords)

	#feature 0,1 matrix 
	
	#calculate p(w1|ci)*..p(wn|ci) 
	#laplace exponential smoothing
	p0Denom=2.0	
	p1Denom=2.0

#p0Denom=0.0
#p1Denom=0.0
	#all sample every class
	for i in range(numTrainDocs):
		if trainCategory[i] == 1:
			p1Num +=trainMartix[i]
			p1Denom+=sum(trainMartix[i])
		else:
			p0Num+=trainMartix[i]
			p0Denom+=sum(trainMartix[i])


	p1Vect = log(p1Num / p1Denom)
	p0Vect = log(p0Num / p0Denom)

	return p0Vect,p1Vect,p1


def classfyNB(vec2Classify,p0Vec,p1Vec,pClass1):

	#assume p(w|ci) =p(w1|ci)*..p(wn|ci)
	p1= sum(vec2Classify*p1Vec)+log(pClass1) #p(w|c1)*p(c1)
	p0= sum(vec2Classify*p0Vec)+log(1-pClass1)

        if p1>p0:
		return 1	
	else:
		return 0


   
#vocabList is Dictionary
def bagOfWords2CecMN(vocabList,inputSet):
	returnVec = [0]*len(vocabList)
	for word in inputSet:
		if word in vocabList:
			returnVec[vocabList.index(word)] +=1

	#inputset word in Dictionary  number
	return returnVec

	

#pCX p(ci|X)
#  0  1
#0 0
#1    0

def MinRisk(RiskMartix,pCx):
	numberClass = len(pCx)
	Risk=zeros(numberClass)

	for i in range(numberClass):
		Risk[i]=sum(RiskMartix[0]*pCx)
	
	Risk=list(Risk)
	
	return Risk.index(min(Risk))




