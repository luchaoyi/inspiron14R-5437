#!/usr/bin/python2.7 
#-*-coding:utf8-*-
#create a test dataSet

def loadDataSet():
    return [[1,3,4],[2,3,5],[1,2,3,5],[2,5]]
#all item list

#将数据集所有单个物品扫描出来
def createC1(dataSet):
    C1=[]
    #对每一个记录
    for transaction in dataSet:
        #记录中每一项
        for item in transaction:
            # --> item in c1?? not  --> exec 
            if not [item] in C1:
                C1.append([item])
    C1.sort()
    return map(frozenset,C1)
#calculate Ck all item support return > minSupport  item and filter < minSupport
# D:type set
# Ck type set

#aprior
#每个项集支持度 = 项集在记录出现次数/总记录数
#关联规则置信度 A-->B = 支持度(A,B)/支持度(A)
#D=map(set,dataSet)
#Ck是项集k代表了项集此时元素个数
def scanD(D,Ck,minSupport):
    ssCnt = {}
    for tid in D:
        for can in Ck:
            #can in tid??
            #Ck每一项(项集)在记录中出现次数
            if can.issubset(tid):
                if not ssCnt.has_key(can):
                    ssCnt[can] = 1
                else:
                    ssCnt[can] += 1
    #affairs record number 
    numItem = float(len(D))
    retList = []
    supportData = {
            }
    for key in ssCnt:
        support = ssCnt[key] / numItem
        if support >= minSupport:
            retList.insert(0,key)
        supportData[key] = support 
    return retList,supportData

#Lk
#Lk item  
def aprioriGen(Lk,k):
    retList=[]
    lenLk = len(Lk)
    for i in range(lenLk):
        for j in range(i+1,lenLk):
            L1 = list(Lk(i))[:k-2];L2 = list(Lk[j])[:k-2]
            L1.sort();L2.sort()
            #Lk SET type
            #merge just append one Element so while 0:K-2 == then the k-1(end) not equal --> new  
            #因为0:k-2个都一样最后一个肯定不一样肯定可以得到一个新记录
            if L1 == L2: #while pre K-2  ==  append
                retList.append(Lk[i] | LK[j])
    
    return retList

def apriori(dataSet,minSupport=0.5):
    C1=createC1(dataSet)
    D=map(set,dataSet)
    L1,supportData = scanD(D,C1,minSupport)
    L=[L1]
    k=2
    while (len(L[k-2]) > 0):
        Ck = aprioriGen(L[k-2],k)
        Lk,supK = scanD(D,Ck,minSupport)
        # supportData is a dict
        supportData.update(supK)
        L.append(Lk)
        k+=1
    return L,supportData 


# L contain all frequent item set 
# L like [
#[freqSet(1,2,3),freqSet(4,5,6)]
#[freqSet(7,8,9),freqSet(10,11,12)]
#       ]
#L[i] is a list every Element is frozenset (frequent item) 
#
def generateRules(L,supportData,minConf = 0.7):
    
    bigRuleList = []

    for i in range(1,len(L)):
        for freqSet in L[i]:
            # for every freqSet find association rules

            H1 = [frozenset([item]) for item in freqSet]
            if len(freqSet) >1:
                rulesFromConseq(freqSet,H,supportData,br1,minConf)
            else:
                calcConf(freqSet,H,supportData,br1,minConf)

            

# conf{a->b} = s(a,b) / s(a)
#calculate confidence and delete < minConf H
def calcConf(freqSet,H,supportData,br1,minConf = 0.7):
    prunedH = []

    
    #conseq in H -->rules  freqSet-conseq --> conseq (freqSet-conseq,conseq)/(freqSet-conseq)
    for conseq in H:
        conf = supportData[freqSet] / supportData[freqSet-conseq]

        if conf >= minConf:
            print freqSet-conseq,'--->',conseq,'conf:',conf

            br1.append((freqSet-conseq,conseq,conf))

            prunedH.append(conseq)

    # satisfy minSupport H
    return prunedH

        

#use rulesFromConseq recursion generate rules
#use calcConf calculate and gather solution
def rulesFromConseq(freqSet,H,supportData,br1,minConf=0.7):
    
    m=len(H[0])

    # len(premise) + len(infersolution) = len(freqSet) while  len(premise)=1 len(infersolution) = m-1
    # m - (m-1)  = 1
    # len(freqSet) - len(H[0]) > 1
    if (len(freqSet) > m+1):
        Hmp1 = aprioriGen(H,m+1)
        Hmp1 = calcConf(freqSet,Hmp1,supportData,br1,minConf = 0.7)
        if(len(Hmp1)>1):
            rulesFromConseq(freqSet,Hmp1,supportData,br1,minConf)


