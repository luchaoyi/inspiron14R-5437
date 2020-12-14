#!/usr/bin/python2.7 
#-*-coding:utf8-*-



from numpy import *

def loadSimpleDataSet():
    dataMat = matrix([[1.,2.1],
            [2.,1.1],
            [1.3,1.],
            [1.,1.],
            [2.,1.]])


    classLabels = [1.0,1.0,-1.0,-1.0,1.0]

    return dataMat,classLabels


def loadDataSet(filename):
    
    fr = open(filename)
    dataMat=[]
    labelMat=[]
    
    #'feature1','feature2',...'classLabel\n' numFeat=len - 1 
    numFeat = len(fr.readline().split('\t'))-1


    for line in fr.readlines():
        lineArr=[]

        currLine = line.strip().split('\t')
            
        #start 0 - m-1 
        for i in range(numFeat):
            lineArr.append(float(currLine[i]))

        dataMat.append(lineArr)
        labelMat.append(float(currLine[-1]))

    return dataMat,labelMat




#
# threshVal:thres value divide 
# threshIneq select 'lt'(less than <) or not
def stumpClassify(dataMatrix,dimen,threshVal,threshIneq):
    retArray = ones ((shape(dataMatrix)[0],1)) #m*1 all ==1 means divide label 1

    if threshIneq == 'lt':

        #divide -1
        index = dataMatrix[:,dimen] <= threshVal
        #print index
        #index is bool type filter array 
        retArray[index] =-1.0
        #retArray[dataMatrix[:,dimen] <= threshVal] = -1.0
    else:
        retArray[dataMatrix[:,dimen] >threshVal]   = -1.0

    
    return retArray






#decision stump 
#构建弱分类器，这里采用决策树，弱分类器则，构建一层决策树使用一个特征
#D样本数据的权重
def bulidStump(dataArr,classLabels,D):

    dataMatrix = mat(dataArr);labelMat = mat(classLabels).T


    m,n=shape(dataMatrix)

    
    numSteps =10.0 #number of step
    bestStump={};bestClassEst=mat(zeros((m,1)))

    minError=inf



    #every feature 
    #构建单层树桩只使用一个特征，找出最好特征，最好划分点
    for i in range(n):

        rangeMin = dataMatrix[i].min();rangeMax = dataMatrix[i].max()

        #计算决策点跨度,每次搜索时增加值
        stepSize = (rangeMax - rangeMin) / numSteps

        #Sum / number = single

    
        for  j in range(-1,int(numSteps)+1):

            for inequal in ['lt','ht']:
                #threshVal rangeMin-stepSize -->add->rangeMax+stepSize
                threshVal = (rangeMin+float(j)*stepSize)

                predictedVals = stumpClassify(dataMatrix,i,threshVal,inequal)

                errArr = mat(ones((m,1)))
                
                #array,与mat 比较后返回True,False，可以将其传到index处True 选项被选中
                #将相等的置0
                errArr[predictedVals == labelMat] =0

                #every sample have weight
                #error weight sum 
                weightedError = D.T*errArr #D的权作用体现在此处，权大的说明上次被错分所以这次如果再错分则会促使
                #weightedError变的更大，而算法训练弱分类器时选择最小误差的这样促使弱分类器将正确分类错误样本 
                #所以如果在错分上次错分的样本成本更大，这样对于错分此样本的分类器，
                #就会更大概率错失成为最佳分类器,而最佳的分类器，倾向于将其正确分类
                
                if weightedError < minError:
                    minError = weightedError
                    
                    bestClassEst = predictedVals.copy()
                    bestStump['dim'] = i
                    bestStump['Ineq'] = inequal 
                    bestStump['thresh'] = threshVal 
    return bestStump,minError,bestClassEst

 

#train single stump
def adaBoostTrainDS(dataArr,classLabels,numIt = 40):
     
     weakClassArr=[]
     m=shape(dataArr)[0]

     D=mat(ones((m,1))/m)

     aggClassEst = mat(zeros((m,1)))

     #loop create tree ->error rate ->0.0
     #tree number according to error rate
     #循环构建弱决策树
     for i in range(numIt):
         #构建
         bestStump ,error,classEst = bulidStump(dataArr,classLabels,D)
         print "D",D.T

         #if error == 0           / 1e-16
         #计算权重
         alpha = float(0.5*log((1.0-error)/max(error,1e-16)))
             

         bestStump['alpha'] = alpha

         weakClassArr.append(bestStump)

         print "classEst",classEst.T

         #classLabels.T*classEst -> equal  ==1 e^alpha, else e^-alpha
         #更新D
         #样本相同，决策树不同因为利用了D权值，新的决策树，倾向于克服上个树的错误
         expon = multiply(-1*alpha*mat(classLabels).T,classEst)

         D=multiply(D,exp(expon))


         D = D/D.sum()

         #class predict accumulate
         #aggClassEst是当前分类器结果的累加
         #每一个分类×alpha权值,得到了一个浮点数，用sign转化为分类计算当前分类误差值
         aggClassEst +=alpha*classEst 
         print "aggClassEst:",aggClassEst 
         aggErrors = multiply(sign(aggClassEst) != mat(classLabels).T,ones((m,1)))

         errorRate = aggErrors.sum()/m
         print "total error:",errorRate,"\n"

         if errorRate == 0.0: 
             break
     return weakClassArr 



def adaClassify(dataToClass,classifierArr):
    dataMatrix=mat(dataToClass)
    m=shape(dataMatrix)[0]
    
    aggClassEst = mat(zeros(m,1))

    for i in range(len(classifierArr)):
        classEst = stumpClassify(dataMatrix,classifierArr[i]['dim'],classifierArr[i]['thresh'],classifierArr[i]['Ineq'])

        aggClassEst +=classifierArr[i]['alpha']*classEst

    

    print aggClassEst
    return sign(aggClassEst)



 


