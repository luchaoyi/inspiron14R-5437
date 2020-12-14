#!/usr/bin/python2.7 

from numpy import *




def loadDataSet(fileName):

    dataMat = []
    fr = open(fileName)

    for line in fr.readlines():
        curLine = line.strip,split('\t')
        fltLine =map(float,curLine) 
        dataMat.append(fltLine)

    return dataMat


def distEclud(vecA,vecB):
    return sqrt(sum(power(vecA - vecB,2)))


# k centroid
def randCent(dataSet,k):
    import random 
    
    n=shape(dataSet)[1]

    centroid = mat(zeros((k,n)))
    for i in range(n):
        minJ = min(dataSet[:,j])

        rangeJ = float(max(dataSet[:,j] - minJ))
        #random.rand(m,n) in numpy create rand array m*n 
        centroid[:,j]=minJ + rangeJ*random.rand(k,1)


    return centroid



def kMeans(dataSet,k,distMeas = distEclud,createCnt = randCent):

    m,n = shape(dataSet)

    #2 dim one is index one is dist**2 centroid
    # sum clusterAssment[1] is SSE(Sum of square error)
    clusterAssment=mat(zeros((m,2)))
    centroid = randCent(dataSet,K)
    #while class centroid not change stop 
    #else loop
    #calculate distEclud
    #flag
    #calculate centroid
    clusterChanged = True
    while clusterChanged:
        clusterChanged = False
        for i in range(m):
            minDist = inf;minIndex = -1
            for j in range(k):
                #sample I --> cluster j distance
                distJI = distEclud(centroid[j,:],dataSet[i,:],)

                if minDist > distJI:
                    minDist = distJI
                    minIndex = j

            #while every sample class flag hasn't changed loop stop
            if clusterAssment[i,0] !=minIndex:
                clusterChanged = True
            clusterAssment[i,:] = minIndex,minDist**2

        for cent in range(k):
            # filter functin filter class flag k
            # select flag k sample m1*n matrix
            # 
            ptsInClust = dataSet[nonzero(clusterAssment[:,0].A == cent)[0]]

            #k centroid k*n vector --> n dim space k point
            #axix =0 --> cal mean according to the column
            centroid[cent,:] = mean(ptsInClust,axis=0)

    return centroid,clusterAssment


def biKmeans(dataSet,k,distMeas = distEclud):
    m  = shape(dataSet)[0]

    clusterAssment = mat(zeros((m,2)))

    #initial only one cluster all is a cluster
    centroid0 = mean(dataSet,axis = 0 ).tolist()[0]
    centlist = [centroid0]

    for j in range(m):
        #every sample error^2
        clusterAssment[j,1] = distEclud(mat(centroid0),dataSet)**2

    #split cluster --> k
    while(len(centlist) < k):
        lowestSSE = inf
        for i in range(len(centlist)):
            # filter current cluster data sample 
            ptsInCurrCluster = dataSet[nonzero(clusterAssment[:,0].A == i )[0],:]
            centroidMat,splitClusstAss  = kMeans(ptsInCurrCluster,2,distMeas)

            #split cluster i calculate SSE 
            sseSplit = sum (splitClusstASS[:,1])
            # other not split SSE
            sseNotSplit = sum(clusterAssment[nonzero(clusterAssment[:,0].A !=i)[0],1])

            #After split i SUM SSE
            # try every cluster to find best cluster to split
            if sseSplit + sseNotSplit < lowestSSE:
                lowestSSE = sseNotSplit+sseSplit 
                bestCentToSplit = i
                bestNewCents = centroidMat
                bestClustAss = splitClusstAss.copy()

        #update class flag 
        bestClustAss[nonzero(bestClustAss[:,0] == 1)[0],:0] = len(centlist) #new cluster

        bestClustAss[nonzero(bestClustAss[:,0] == 0)[0],:0] = i

        
        #append the cenlist and clusterAssment

        centlist[bestCentToSplit] = bestNewCents[0,:]
        cenlist.append(bestNewCents[1,:])


        clusterAssment[nonzero(clusterAssment[:,0]==bestCentToSplit)[0],:] = bestClustAss 

    return mat(cenlist),clusterAssment
