#!/usr/bin/python2.7 
#-*-utf8-*-
from numpy import *



#read
#split
#format
#append
def loadDataSet(filename):

    dataMat=[]
    fr = open(filename);

    for line in fr.readlines():

        curline = line.strip().split('\t')
        fltLine = map(float,curline)
        dataMat.append(curline)

    return dataMat

#leaf node is solution
#input a sample -> tree  -->leaf node -->get a value is y mean 
def regLeaf(dataSet):
    return mean(dataSet[:,-1])

def regErr(dataSet):
    return var(dataSet[:,-1])*shape(dataSet)[0]

def binSplitDataSet(dataSet,feature,value):
    #nonzero() filter function return r,c type array
    #while c==const only return r
    #please read doc get more information

    mat0=dataSet[nonzero(dataSet[:,feature]>value)[0],:][0]
    mat1=dataSet[nonzero(dataSet[:,feature]<value)[0],:][0]

    return mat0,mat1

#create tree node function regLeaf
#calculate error function regErr

def createTree(dataSet,leafType=regLeaf,errType=regErr,ops=(1,4)):

    #select best feature
    feat,val = chooseBestSplit(dataSet,leafType,errType,ops)

    if feat == None :
        return val

    retTree={}
    retTree['spInd'] = feat
    retTree['spVal'] = val 
    #split
    lSet,rSet = binSplitDataSet(dataSet,feat,val)
    
    retTree['left']     =   createTree(rSet,leafType,errType,ops)
    retTree['right']    =   createTree(lSet,leafType,errType,ops)

    return retTree










#choose best feature and split value 
#return feat and val
#calculate split error select best split
#ops control split stop 
def chooseBestSplit(dataSet,leafType,errType,ops):

#使用tols和tolN进行了预剪枝。
#tols控制了节点(基于errType度量)的纯度改善的最小阈值
#tolN控制了叶子节点最少样本数
#低于最小阈值则节点不分裂

    tolS = ops[0] #   
    tolN = ops[1] #split min number sample

    #all is same value 
    if len(set(dataSet[:,-1].T.tolist()[0])) == 1:
        return None,leafType(dataSet)
    m,n=shape(dataSet)
    S = errType (dataSet)

    bestS = inf;
    bestIndex = 0;
    bestValue = 0;

    for featIndex in range(n-1):
        for splitVal in set(dataMat[:,featIndex]):
            mat0,mat1 = binSplitDataSet(dataSet,featIndex,splitVal)
            if (shape(mat0)[0] < tolN) or (shape(mat1)[0] <tolN) :
                continue
            # do nothing 
            
            #划分后两个数据集分别计算regErr求和
            newS = errType(mat0)+errType(mat1)
            
            if newS <bestS:
                bestIndex = featIndex
                bestS = newS
                bestValue = splitVal


    
    if (S-bestS) < tolS: # error small -->tolS  form leaf
        return None,leafType(dataSet)
    #use best feature and value but still samll sample set
    mat0,mat1 = binSplitDataSet(dataSet,bestIndex,bestValue)
    if (shape(mat0)[0] < tolN) or (shape(mat1)[0] <tolN) :

        return None,leafType(dataSet)

    return bestIndex,bestValue




#is leaf node
def isTree(obj):

    return (type(obj).__name__ == 'dict' )

#return tree mean 
def getMean(tree):
    
    if isTree(tree['left']):
        tree['left'] = getMean(tree['left'])
    if isTree(tree['right']):
        tree['right'] = getMean(tree['right'])


    return (tree['left'] +tree['right'])/2.0


#if subtree then prune
#if leaf node judge merge

def prune(tree,dataSet):
# prune tree 
# if prune -> node ->merge else return tree 

    if shape(dataSet)[0] == 0 : return getMean(tree)

    #prepare test dataSet
    if isTree(tree['left']) or isTree(tree['right']):
        lSet,rSet = binSplitDataSet(testData,tree['spInd'],tree['spVal'])
    if isTree(tree['left']) :
        tree['left'] = prune(tree['left'],lSet)
    if isTree(tree['right']):
        tree['right'] = prune(tree['right'],rSet)
#after prune judge is or is not node 
    if not isTree(tree['left']) and not isTree(tree['right']):
        lSet,rSet = binSplitDataSet(testData,tree['spInd'],tree['spVal'])

        errorNoMerge = sum(power(lSet[:,-1] - tree['left'],2))+sum(power(rSet[:,-1] - tree['right'],2))

        treeMean = tree['left'] + tree['right']

        errorMerge = sum(power(dataSet[:,-1] - treeMean,2))

        if errorMerge  < errorNoMerge :
            print 'merge'
            return treeMean
        else:
            return tree

    else:
        return tree



# w =(X.T*X)-1X.Ty
def linearSolve(dataSet):
    m,n = shape(dataSet)

    X=mat(ones((m,n)))
    Y=mat(ones(m))

    #x0=1
    #1:n -> [1,n] 
    X[:,1:n] = mat(dataSet[:,0:n-1])
    Y = mat(dataSet[:,-1])


    XTX = X.T*X

    if linalg.det(XTX) == 0.0:
        raise NameError('this matrix is singular,cannot do inverse!')

    ws = XTX.I * (X.T)

    return ws,X,Y

def modelLeaf(dataSet):
    ws,X,Y = linearSolve(dataSet)
    return ws #y=w0*x0+..wi*xi
def modelErr(dataSet):
    ws,X,Y = linearSolve(dataSet)

    yHat = X*ws

    return sum(power(yHat - Y,2))




#leaf node is a value regTree
def regTreeEval(model,inData):
    return float(model)


#leaf node is a linear regression equation
def modelTreeEval(model,inData):
    
    #feature n
    n=shape(inData)[1]

    X=mat(ones(1,n+1))

    X[:,1:n+1] = inData

    return float(X*model)


def treeForeCast(tree,inData,modelEval = regTreeEval):

    if not isTree[tree] :return modelEval(tree,inData)

    if inData[tree['spInd']] > tree['spVal']:
        if isTree(tree['left']):
            return treeForeCast(tree['left'],inData,modelEval)
        else:
            return modelEval(tree,inData)
    else:
        if isTree(tree['right']):
            return treeForeCast(tree['right'],inData,modelEval)
        else:
            return modelEval(tree,inData)


#ForeCast(predict)
def createForeCast(tree,testData,modelEval=regTreeEval):

    m = len(testData)

    yHat = mat(zeros((m,1)))

    for i in range(m):
        yHat[i] = treeForeCast(tree,testData[i],modelEval)

    return yHat



