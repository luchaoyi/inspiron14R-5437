#!/usr/bin/python2.7 


from numpy import *

def loadDataSet(filename):
    dataMat=[] ; labelMat=[]
    fr=open(filename)

    for line in fr.readlines():
        lineArr = line.strip().split()
        
        #1(x0),x1,x2
        dataMat.append([1.0,float(lineArr[0]),float(lineArr[1])])

        labelMat.append(int(lineArr[2]))

    return dataMat,labelMat


def sigmoid(inX):
    return 1.0/(1+exp(-inX))



def gradAscent(dataMatIn,classLabels):

    dataMatrix = mat(dataMatIn)
    
    labelMat = mat(classLabels).transpose()


    m,n=shape(dataMatrix)

    alpha = 0.001

    maxCycles =500
    
    weights = ones((n,1))
    for k in range(maxCycles):
        
        #every sample output
        h = sigmoid(dataMatrix*weights)

        error=(labelMat - h)

        weights = weights+alpha*dataMatrix.transpose()*error

    return weights






def stoGradAscent0(dataMat,classLabels):
    dataMat=array(dataMat)
    m,n = shape(dataMat)
    alpha = 0.01
    weights=ones(n)
    
    for i in range(m):
        h=sigmoid(sum(dataMat[i]*weights))

        error = classLabels[i] - h

        weights = weights+alpha*error*dataMat[i]

    
    weights=mat(weights).T
    return weights




# change alpha
# rand select sample 
def stoGradAscent1(dataMat,classLabels,numIter = 150):

    dataMat=array(dataMat)
    m,n = shape(dataMat)
    weights=ones(n)
    for j in range(numIter):
        dataIndex = range(m)

        for i in range(m):
            alpha=4/(1.0+i+j)+0.01

            randIndex = int(random.uniform(0,len(dataIndex)))

            h=sigmoid(sum(dataMat[randIndex]*weights))
            error = classLabels[randIndex] - h
            weights = weights+alpha*error*dataMat[randIndex]

            del(dataIndex[randIndex])

    
    weights=mat(weights).T
    return weights

def stoGradAscent2(dataMat,classLabels,numIter = 150):

    dataMat=array(dataMat)
    m,n = shape(dataMat)
    weights=ones(n)
    for j in range(numIter):
        dataIndex = range(m)

        for i in range(m):
            alpha=4/(1.0+i+j)+0.01

            randIndex = random.choice(dataIndex)

            h=sigmoid(sum(dataMat[randIndex]*weights))
            error = classLabels[randIndex] - h
            weights = weights+alpha*error*dataMat[randIndex]
                

            del(dataIndex[dataIndex.index(randIndex)])

    weights=mat(weights).T
    return weights


def stoGradAscent3(dataMat,classLabels,numIter = 150):

    dataMat=array(dataMat)
    m,n = shape(dataMat)
    weights=ones(n)
    for j in range(numIter):
        dataIndex = range(m)

        for i in range(m):
            alpha=4/(1.0+i+j)+0.01

            randIndex = int(random.uniform(0,len(dataIndex)))

            h=sigmoid(sum(dataMat[dataIndex[randIndex]]*weights))
            error = classLabels[dataIndex[randIndex]] - h
            weights = weights+alpha*error*dataMat[dataIndex[randIndex]]

            del(dataIndex[randIndex])

    
    weights=mat(weights).T
    return weights


def plotBestFit(wei):
    import matplotlib.pyplot as plt
    
    #matrix to array
    weights = wei.getA()
    
    dataMat ,labelMat = loadDataSet('testSet.txt')

    dataArr = array(dataMat)
    n = shape(dataArr)[0]

    xcord1 = []; ycord1 =[]
    xcord2 = []; ycord2 =[]

    for i in range(n):
        if int(labelMat[i]) == 1:
            xcord1.append(dataArr[i,1]);ycord1.append(dataArr[i,2])
        else:

            xcord2.append(dataArr[i,1]);ycord2.append(dataArr[i,2])

    fig = plt.figure()

    ax = plt.subplot(111)

    ax.scatter(xcord1,ycord1,s=30,c='red',marker='s')
    ax.scatter(xcord2,ycord2,s=30,c='green')

    #array range like range but return array type
    x=arange(-3.0,3.0,0.1)

    y= (-weights[0]-weights[1]*x)/weights[2]

    ax.plot(x,y)

    plt.xlabel('X1');plt.xlabel('X2')
    plt.show()



def classifyVector(inX,weights):
    prob = sigmoid(sum(inX*weights))
    if prob >0.5:
        return 1
    else:
        return 0


 
