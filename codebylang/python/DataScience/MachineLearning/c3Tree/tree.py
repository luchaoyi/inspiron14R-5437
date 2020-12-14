#!/usr/bin/python2.7 



# more information gain(entropy) means provide more information
# select more entropy feature to divide dataSet
from math import log
import operator

# H=-Ep(xi)log2p(xi)
# calculate column n ShannonEnt
def calShannonEnt(dataSet,n):
    #every feature diffrent value and number

    #the number of sample 
    numEntries = len(dataSet)
    labelCounts={}

    for featVec in dataSet:
        currentLabel=featVec[n]

        if currentLabel not in labelCounts.keys():
            labelCounts[currentLabel]=0

        labelCounts[currentLabel]+=1

        shannonEnt = 0.0

        for key in labelCounts:
            prob = float(labelCounts[key])/numEntries

            shannonEnt -= prob*log(prob,2)

    return shannonEnt



def createDateSet():
    dataSet = [[1,1,'yes'],
            [1,1,'yes'],
            [1,0,'no'],
            [0,1,'no'],
            [0,1,'no']
            ]
    featureName = ['no surfacing','flippers']

    return dataSet,featureName


#according to feature axis value divide dataSet
def splitDataSet(dataSet,axis,value):
    retDataSet = []

    for featVec in dataSet:
        if featVec[axis] == value:
            #0->axis)axis (axis+1:)
            #
            reducedFeatVec = featVec[:axis]
            reducedFeatVec.extend(featVec[axis+1:])

            retDataSet.append(reducedFeatVec)
    return retDataSet


def chooseBestFeatureToSplit(dataSet):
    numFeatures = len(dataSet[0]) - 1

    baseEntropy = calShannonEnt(dataSet,-1)

    #init
    bestInfoGain = 0.0
    bestFeature  = -1

    for i in range(numFeatures):
        featList = [example[i] for example in dataSet]
        
        #translate into set reduce the same value
        uniqueVals = set(featList)

        newEntropy = 0.0

        for value in uniqueVals:
            subDataSet = splitDataSet(dataSet,i,value)
            
            #divide data proportion
            prop = len(subDataSet)/float(len(dataSet))
            
            newEntropy+= prop*calShannonEnt(subDataSet,-1)
        infoGain = baseEntropy - newEntropy
        if(infoGain>bestInfoGain):
            bestInfoGain = infoGain
            bestFeature = i

    return bestFeature


#def majorityCnt(dataSet):
#   classCnt={}
#    for featVec in dataSet:
#       key=featVec[-1]
#      if key not in classCnt:
#         classCnt[key]=0
#    classCnt[key] +=1



#input classList eg. ['A','B','A',B'']
def majorityCnt(classList):

    classCnt={}

    for vote in  classList:
        if vote not in classCnt:
            classCnt[vote]=0
        classCnt[vote] +=1

    #sorted return list type
    sortedClassCount = sorted(classCnt.iteritems(),key=operator.itemgetter(1),reverse=True)

    return sortedClassCount[0][0]



def createTree(dataSet,featureName):

    classList = [example[-1] for example in dataSet]

    #all data class same one label count equal all labes count 
    if classList.count(classList[0]) == len(classList):
        return classList[0]
    
    #use all feature data still mixture return class whose count more 
    if len(dataSet[0]) == 1:
        return majorityCnt(classList)

    #1 select best feature
    bestFeat = chooseBestFeatureToSplit(dataSet)
    #divide dataSet
    bestFeatName = featureName[bestFeat]

    myTree = {bestFeatName:{}}

    del(featureName[bestFeat])

    featValues = [example[bestFeat] for example in dataSet]

    uniqueVals = set(featValues)

    for value in uniqueVals:
        subfeatname = featureName[:]
        myTree[bestFeatName][value] = createTree(splitDataSet(dataSet,bestFeat,value),subfeatname)


    return myTree





#1 analysis root get dict [featureValue1:subSet,featureValue2:subSet...]
#2 according feature  visit tree
def classify(inputTree,featName,testVec):
    firstStr = inputTree.keys()[0]
    
    secondDict = inputTree[firstStr]

    #get feature index in testVec
    featIndex = featName.index(firstStr)
    
    #according feature classify
    for key in secondDict.keys():
        if testVec[featIndex] == key:
            if type(secondDict[key]).__name__ == 'dict':
                classLabel = classify(secondDict[key],featName,testVec)
            else:
                classLabel = secondDict[key]
    return classLabel



def storeTree(inputTree,filename):
    import pickle
    fw = open(filename,'w')

    pickle.dump(inputTree,fw)

    fw.close();

def loadTree(filename):
    import pickle

    fr = open(filename)

    return pickle.load(fr)


    

