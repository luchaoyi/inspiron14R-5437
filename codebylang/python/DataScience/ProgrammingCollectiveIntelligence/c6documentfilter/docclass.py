
#-*-coding:utf8-*-

import re 
import math



def getwords(doc):
    splitter=re.compile('\\W*')

    words=[s.lower for s in splitter.split(doc) if lens>2 if lens < 20]

    #返回不重复单词，dict set
    return dict([(w,1) for w in words])

class classifier:
    def __init__(self getfeatures,filename=None):
        
        #统计特征（单词）在各分类中出现的次数
        self.fc={}
        self.cc={}
        # getfeatures 是提取特征的函数
        self.getfeatures=getfeatures

    #生成fc,f:feature
    #{f:{c1:num1,c2:num2}}
    def incf=(self,f,cat):
        self.fc.setdefault(f,{})
        self.fc[f].setdefault(cat,0)
        self.fc[f][cat]+=1

    def incc(self,cat):
        self.cc.setdefault(cat,0)
        self.cc[cat]+=1

    # count(f|cat) cat分类下的f出现次数
    def fcount(self,f,cat):
        if f in self.fc and cat in self.fc[f]:
            return float(self.fc[f][cat])
        return 0.0 

    #每一个分类的数量
    def catcount(self,cat):
        if cat in self.cc:
            return float(self.cc[cat])
        return 0.0

    def totalcount(self):
        return sum(self.cc.values())

    #所有分类列表
    def categories(self):
        return self.cc.keys()

    #train 接受一个文档内容和分类
    def train(self.item,cat):
        features=self.getfeatures(item)

        for f in features:
            self.incf(f,cat)

        self.incc(cat)

    #计算 p(f|ci)= f出现次数/文档总数 特征出现次数
    #这里没有利用一篇文档所有词语做词袋模型，而是提取特征时将文章，过滤为所有不重复的单词
    def fprob(self,f,cat):
        if self.catcount(cat) == 0: return 0
        return self.fcount(f,cat)/seltf.catcount(cat)

    #初始给一个概率猜测，平滑作用（拉普拉斯平滑同作用）避免每出现的概率为0

    #函数计算的是P(xi|ci),一个单词
    def weightedprob(self,f,cat,prf,weight=1.0,ap=0.5):
        
        basicprob=prf(f,cat)
        
        #统计f总共出现次数，概率是对f初始假设与实验情况加权，不管f出现在哪个类中
        #出现次数越多说明信息量越大，初始假设权值越小
        totals=sum([self.fcount(f,c) for c in self.categories])

        #这里算得是f在某个类的概率但是加权 用的是f出现的总数
        bp=((weight*ap)+(totals*basicprob))/(weight+totals)

        return bp


#最终需要比较 p(ci|X) 的概率  P(ci|X) = P(X|ci)P(ci) / P(X)

#对于分类时针对实际情况可以设置阈值，即相当于对错分设置成本
#将文档错分为此类的成本作为权值在比较时与概率相乘
#这里采用设定一个值，代表分到此类需几倍与其它类概率，异曲同工


class naivebayes(classifier):
    #假设特征独立 p(X|ci)

    def __init__():
        #子类有构造 函数时不会自动调用父类构造函数
        classifier.__init__(self,getfeatures)
        self.thresholds={}

    def setthreshold(self,cat,t):
        self.thresholds[cat]=t

    def getthreshold(self,cat):
        if cat not in self.thresholds: return 1.0
        return self.thresholds[cat]

    def docprob(self,item,cat):
        features=self.getfeatures(item)

        p=1

        #p(F|ci) = P(f1|ci)*...
        for f in features:p*=self.weightedprob(f,cat,self.fprob)
        return p

    def prob(self,item,cat):
        catprob=self.catcount(cat) / self.totalcount()
        docprob=self.docprob(item,cat)

        return docprob*catprob 

    def classify(self,item,default=None):
        probs={}
    
        max=0.0


        #计算属于每一类的概率并找出最大的
        for cat in self.categories():
            probs[cat]=self.prob(item,cat)
            if probs[cat] > max:
                max=probs[cat]
                best=cat 

        return best 


