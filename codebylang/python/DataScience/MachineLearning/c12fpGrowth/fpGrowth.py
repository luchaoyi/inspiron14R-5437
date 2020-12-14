#!/usr/bin/python2.7 
#-*-coding:utf8-*-
#FP 算法思想是 创建基础原始FP树后对每个基本元素从FP树中抽取条件基，组成和此元素共现的数据记录集合
#然后用此数据集创建此元素的专属FP树 称为条件FP树，然后从此树抽取基，递归则发现一组 共现规则

class treeNode:
    def __init__(self,nameValue,numOccur,parentNode):
        self.name = nameValue
        self.count = numOccur
        self.nodeLink = None
        # FP tree while construct record parentNode in data field
        self.parent = parentNode
        self.children ={} # name:node 

    def inc(self,numOccur):
        self.count += numOccur

    def disp(self,ind=1):
        print ' '*ind,self.name,' ',self.count

        for child in self.children.values():
            child.disp(ind+1)

def updateTree(items,inTree,headerTable,count):

    if items[0] in inTree.children:
        inTree.children[items[0]].inc(count)
    else:
        inTree.children[items[0]] = treeNode(items[0],count,inTree)

        if headerTable[items[0]][1] == None:
            headerTable[items[0]][1] = inTree.children[items[0]]
        else:
            updateHeader(headerTable[items[0]][1],inTree.children[items[0]])

    if len(items)>1:
        updateTree(items[1::],inTree.children[items[0]],headerTable,count)



def updateHeader(nodeToTest,targetNode):
    
    while (nodeToTest.nodeLink != None):
        nodeToTest=nodeToTest.nodeLink

    nodeToTest.nodeLink = targetNode

#dataSet is a dict  frozenset(['a','b','c']):1   record:number
def createTree(dataSet, minSup=1): #create FP-tree from dataset but don't mine
    headerTable = {}

    #1.先扫描数据集每个记录每个元素构造头指针表，统计每单个出现次数，并删除出现少于minSup次数的元素
    #go over dataSet twice
    for trans in dataSet:#first pass counts frequency of occurance
        for item in trans:
            headerTable[item] = headerTable.get(item, 0) + dataSet[trans] #+1
    for k in headerTable.keys():  #remove items not meeting minSup
        if headerTable[k] < minSup: 
            del(headerTable[k])
    freqItemSet = set(headerTable.keys())
    #print 'freqItemSet: ',freqItemSet
    if len(freqItemSet) == 0: return None, None  #if no items meet min support -->get out
    for k in headerTable:
        headerTable[k] = [headerTable[k], None] #reformat headerTable to use Node link 
    #print 'headerTable: ',headerTable


    #2.构建树
    retTree = treeNode('Null Set', 1, None) #create tree
    for tranSet, count in dataSet.items():  #go through dataset 2nd time
        localD = {}
        #扫描数据集对每个记录构造路径，过滤掉那些不频繁的元素
        for item in tranSet:  #put transaction items in order
            if item in freqItemSet:
                localD[item] = headerTable[item][0]
        if len(localD) > 0:
            orderedItems = [v[0] for v in sorted(localD.items(), key=lambda p: p[1], reverse=True)]
            updateTree(orderedItems, retTree, headerTable, count)#populate tree with ordered freq itemset
    return retTree, headerTable #return tree and header table


def ascendTree(leafNode,prefixPath):

    if leafNode.parent!=None:
        prefixPath.append(leafNode.name)
        ascendTree(leafNode.parent,prefixPath)

def loadSimpDat():
    simpDat = [['r', 'z', 'h', 'j', 'p'],
               ['z', 'y', 'x', 'w', 'v', 'u', 't', 's'],
               ['z'],
               ['r', 'x', 'n', 'o', 's'],
               ['y', 'r', 'x', 'z', 'q', 't', 'p'],
               ['y', 'z', 'x', 'e', 'q', 's', 't', 'm']]
    return simpDat

def createInitSet(dataSet):
    retDict = {}
    for trans in dataSet:
        retDict[frozenset(trans)] = 1
    return retDict

# find a headerTable -> link list all path
def findPrefixPath(basePat,treeNode):
    condPats ={
            }

    while treeNode != None:
        prefixPath=[]
        ascendTree(treeNode,prefixPath)

        if len(prefixPath)>1:
            condPats[frozenset(prefixPath[1:])] = treeNode.count

        treeNode = treeNode.nodeLink

    return condPats 


#递归构建的过程
#初始FP树扫描整个数据集构建的，然后挖掘频繁项集
#频繁项集从单个元素开始生成，利用的是条件FP树 
#访问FP树，从headerTable开始发现某元素前缀路径过滤出 此元素条件下的频繁项集,生成的数据集为此元素条件下的数据集
#然后利用此数据集，进一步构造出FP树   FP|* 下的FP树，然后从此FP|*中递归过程 FP|*|** --> FP|*|**|*** ...
def mineTree(inTree,headerTable,minSup,preFix,freqItemList):
    
    bigL = [v[0] for v in sorted(headerTable.items(),key = lambda p:p[1])]
    
    # headerTable sorted bigL base element 
    for basePat in bigL:
        # freqSet = prefixPath + basePat  t:s,x,z == (t,s,x,z)
        newFreqSet = preFix.copy()

        newFreqSet.add(basePat)

        freqItemList.append(newFreqSet)
        # find pre path 
        condPattBases = findPrefixPath(basePat,headerTable[basePat][1])
        #every element create CondTree
        # according pre path set create CondTree
        # one element FP tree with element appear
        # <minSup while create Tree filter
        myCondTree,myHead = createTree(condPattBases,minSup)

        if myHead != None:
            mineTree(myCondTree,myHead,minSup,newFreqSet,freqItemList)



