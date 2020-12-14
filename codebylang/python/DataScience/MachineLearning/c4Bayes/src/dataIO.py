# -*-coding: utf-8 -*-

from numpy import *
from numpy import linalg as la

import os
import chardet
import copy #对象复制模块



#字符列表转为一个字符串
def listToUnicode(ulist):
    ustr=""

    for element in ulist:
        ustr+=element

    return ustr

#文件读取
#E 读取英文
#C 读取中文

def textParse(bigString):    #input is big string, #output is word list
    import re
    listOfTokens = re.split(r'\W*', bigString)
    return [tok.lower() for tok in listOfTokens if len(tok) > 2] 
def readfileE(filepath):
    wordlist=[]
    linelist=[]
    filelist = os.listdir(filepath)
    for  file in filelist:
        f= open(filepath+"/"+file)


        for line in f.readlines():
            linelist = textParse(line)
            
            wordlist.append(linelist)
            linelist=[]
    return wordlist
    

    
def readfileC(filepath,code='utf8'):
    wordlist=[]
    linelist=[]
    filelist = os.listdir(filepath)
    for  file in filelist:
        f= open(filepath+"/"+file)


        for line in f.readlines():
            #fencoding=chardet.detect(line)['encoding']
            #print line
            #print "----------------------"
            Uline=unicode(line,code)
            linelist=[] #warn!-----------------
            for wd in Uline:
                if wd != u' ':
                    linelist.append(wd)
            #print listToUnicode(linelist)
            #print"---------------------------"
            wordlist.append(linelist)
    return wordlist

#文件读取
#E 读取英文
#C 读取中文
#读取一个文件夹下所有文件，每一行文字，生成一个列表，返回的是列表的列表
def readfile(path,language="C",code='utf8'):
    if language == 'C':
        wordList=readfileC(path,code)
    else:
        wordList=readfileE(path)
    return wordList


def createVocabList(dataSet):
    vocabSet = set([])  #create empty set
    for document in dataSet:
        vocabSet = vocabSet | set(document) #union of the two sets
    return list(vocabSet)


#不计词频
def setOfWords2Vec(vocabList, inputSet):
    returnVec = [0]*len(vocabList)
    for word in inputSet:
        if word in vocabList:
            returnVec[vocabList.index(word)] = 1
        #else:
            #print "the word: %s is not in my Vocabulary!" % word

    return returnVec

def Vec2WordSet(vocabList,inputVec):
    returnWord = []
    l=len(inputVec)

    for  i in range(l):
        if  inputVec[i]==1:
            returnWord.append(vocabList[i])
        #else:
            #print "the word: %s is not in my Vocabulary!" % word
    return returnWord
    
#计词频
def bagOfWords2VecMN(vocabList, inputSet):
    returnVec = [0]*len(vocabList)
    for word in inputSet:
        if word in vocabList:
            returnVec[vocabList.index(word)] += 1
    return returnVec
    
def genDataVec(path,language="C",code='utf8'):
    #读入数据
    wordlist=readfile(path,language,code)
    #生成字典
    myVocabList=createVocabList(wordlist)
    #生成向量
    trainMat=[]
    for postinDoc in wordlist:
        trainMat.append(setOfWords2Vec(myVocabList, postinDoc))
    return mat(trainMat),myVocabList,listOPosts
        
def genDataVecMN(path,language="C",code='utf8'):
    #读入数据
    wordlist=readfile(path,language,code)
    #生成字典
    myVocabList = createVocabList(wordlist)
    #生成向量
    trainMat=[]
    for postinDoc in wordlist:
        trainMat.append(bagOfWords2VecMN(myVocabList, postinDoc))
    return mat(trainMat),myVocabList,wordlist

def genLabels(trainMat,label):
    labels=[label]*len(trainMat)
    return labels 

#输出分类结果到文件
#k指定结果分为几类，则打开几个文件
def Classify2File(listOPosts,ClassLabels,k):
    fileList=[]
    
    for i in range(k):
        fileList.append(open(str(i)+'.txt','w'))

	
    for i in range(len(listOPosts)):
        label = ClassLabels[i]
        ustr=listToUnicode(listOPosts[i])

        fileList[label].write(ustr.encode('utf8'))

    for i in range(k):
        fileList[i].close()
