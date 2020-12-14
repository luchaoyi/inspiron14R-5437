#!/usr/bin/python2.7 
#-*-coding:utf8-*-


from numpy import *
import operator 


def createDataSet():
    group = array([[1.0,1.1],[1.0,1.0],[0,0],[0,0.1]])
    labels=['A','A','B','B']
    
    return group,labels


#inX input vector
def classify0(inX,dataSet,labels,k):
    dataSetSize = dataSet.shape[0]

    #extend inX 
    diffMat = tile(inX,(dataSetSize,1)) - dataSet
    sqDiffMat = diffMat**2
    sqDistances = sqDiffMat.sum(axis=1)
    
   
    distances = sqDistances**0.5
    sortedDistIndicies = distances.argsort()#return index
    classCount={}
    for i in range(k):
        voteIlabel = labels[sortedDistIndicies[i]]
        #get(voteIlabel,0) visit classCount[voteIlabel] if non-existent
        classCount[voteIlabel] = classCount.get(voteIlabel,0)+1
        #dict sort return [()]  eg:[('A',1),('B',2)]
    sortedClassCount = sorted(classCount.iteritems(),key=operator.itemgetter(1),reverse=True)
    return sortedClassCount[0][0]



#read line to array 1:open file 2:matrix m*n??3:for file2matrix
def file2matrix(filename,n):
    fr=open(filename)
    arrayOLines = fr.readlines() #read all file ->list
    numberoflines = len(arrayOLines) #m sample

    returnMat = zeros((numberoflines,n));
    classLabelVector=[]
    index = 0

    #40920  8.326976    0.953952    3(largeDoses)
    #data format
    #Data analysis
    for line in arrayOLines:
        line =line.strip()#delete head lstrip() tail rstrip() 
        listFormatLine = line.split('\t')
        
        returnMat[index,:] = listFormatLine[0:n]#[0,n)  >> 0-n-1
        classLabelVector.append(int(listFormatLine[-1]))

        index=index+1

    return returnMat,classLabelVector




#(x-min) / (max -min) ->0,1 
def autoNorm(dataSet):

    #0 select column min  max
    minVals = dataSet.min(0)
    maxVals = dataSet.max(0)

    ranges = maxVals - minVals

    normDataSet = zeros(shape(dataSet))
    
    m = dataSet.shape[0]
    normDataSet = dataSet - tile(minVals,(m,1))
    normDataSet = normDataSet/tile(ranges,(m,1))

    return normDataSet,ranges,minVals


def datingClassTest(trainDatafilename,n):
    hoRatio = 0.10

    datingDataMat,datingLabels = file2matrix(trainDatafilename,n)
    normDataSet,ranges,minVals = autoNorm(datingDataMat)

    #mat.shape return [r,c]
    m = normDataSet.shape[0] # number of sample m
    #10% test
    numTestVecs = int (m*hoRatio)
    
    errorCount = 0.0
    for i in range(numTestVecs):
        
        #online study A large amount of calculation
        classifierResult = classify0(normDataSet[i,:],normDataSet[numTestVecs:m,:],\
                datingLabels[numTestVecs:m],n)

        print "classifierResult %d ,the real answer %d" %(classifierResult,datingLabels[i]);



        if(classifierResult != datingLabels[i]):
            errorCount += 1.0

    print "the error rate is %f" %(errorCount/float(numTestVecs))




#data m*n
def img2vector(filename,m,n):
    returnVect = zeros(1,m*n)

    fr=open(filename)
    for in range(m):
        lineStr = fr.readline()
        for j in range(n):
            returnVect[0,m*i,+j] = int(lineStr[j])

    return returnVect




