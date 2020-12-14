#!/usr/bin/python 
#-*-coding:utf8-*-

import sqlite3
from math import tanh


def dtanh(y):
    return 1.0-y*y

#本例中不预先构建好网络而是旨在需要时构建,相应的隐藏节点
#每传入一组未见过的单词组合，建立一个关联的隐藏节点，不是全连接的那种，一种单词组合，对应一个隐藏节点与其它不关联
class searchnet:
    def __init__(self,dbname):
        self.con=sqlite3.connect(dbname)

    def __del__(self):
        self.con.close()
    
    def dbcommit(self):
        self.con.commit()

    def maketables(self):
        self.con.execute('create table hiddennode(create_key)')
        #word --> hidden -->url 三层神经网络 
        self.con.execute('create table wordhidden(fromid,toid,strenth)')
        self.con.execute('create table hiddenurl(fromid,toid,strenth)')
        self.dbcommit()

    def getstrenth(self,fromid,toid,layer):
        if layer==0: table='wordhidden'
        else: table='hiddenurl'
        res=self.con.execute('select strenth from %s where fromid=%d and toid=%d' % (table,fromid,toid)).fetchone()
        if res == None:
            if layer==0: return -0.2
            if layer==1: return 0
        
        return res[0]


    def setstrength(self,fromid,toid,layer,strenth):
        if layer==0: table='wordhidden'
        else: table='hiddenurl'
        res=self.con.execute('select rowid from %s where fromid=%d and toid=%d' % (table,fromid,toid)).fetchone()

        #如果没有记录则插入新记录
        if res == None:
            self.con.execute('insert into %s (fromid,toid,strenth) values (%d,%d,%f)' % (table,fromid,toid,strenth))

        else:
            rowid=res[0]
            self.con.execute('update %s set strenth=%f where rowid=%d' %(table,strenth,rowid))

    
    def generatehiddennode(self,wordids,urls):
        
        #limit words <= 3
        if len(wordids) > 3: return None 

        #'w0_w1_w2'
        createkey='_'.join(sorted([str(wi) for wi in wordids]))
        res=self.con.execute(
                'select rowid from hiddennode where create_key="%s"' % createkey).fetchone()


        #不同输入词组->一个隐藏节点-->产生相关url连接。构造了一个非全连接神经网络
        if res == None:
            cur=self.con.execute(
                    'insert into hiddennode (create_key) values ("%s")' % createkey)

            hiddenid=cur.lastrowid

            for wordid in wordids:
                self.setstrength(wordid,hiddenid,0,1.0/len(wordids))

            for urlid in urls:
                self.setstrength(hiddenid,urlid,1,0.1)

            self.dbcommit()

    def getallhiddenids(self,wordids,urlids):
        l1={}
        for wordid in wordids:
            cur=self.con.execute(
                    "select toid from wordhidden where fromid=%d" % wordid)
            for row in cur: l1[row[0]] = 1
        for urlid in urlids:
            cur=self.con.execute(
                    "select fromid from hiddenurl where toid=%d" % urlid)
            for row in cur: l1[row[0]] = 1
        return l1.keys()
    

    def setupnetwork(self,wordids,urlids):

        #神经网络三层节点
        self.wordids=wordids
        self.hiddenids=self.getallhiddenids(wordids,urlids)
        self.urlids=urlids

        self.ai=[1.0]*len(self.wordids)
        self.ah=[1.0]*len(self.hiddenids)
        self.ao=[1.0]*len(self.urlids)

        self.wi=[[self.getstrenth(wordid,hiddenid,0)
            for hiddenid in self.hiddenids]
            for wordid in self.wordids]

        self.wo=[[self.getstrenth(hiddenid,urlid,1)
            for urlid in self.urlids]
            for hiddenid in self.hiddenids]


    def feedforward(self):
        
        for i in range(len(self.wordids)):
            self.ai[i]=1.0

        for j in range(len(self.hiddenids)):
            sum=0.0

            #第j个隐藏节点输出等于所有连接到j上的输入
            for i in range(len(self.wordids)):
                sum+=self.ai[i]*self.wi[i][j]

            self.ah[j]= tanh(sum)
        #输出层
        for k in range(len(self.urlids)):
            sum=0.0
            for j in range(len(self.hiddenids)):
                sum+=self.ah[j]*self.wo[j][k]
            self.ao[k]=tanh(sum)

        #返回不是ao的引用，而返回的是ao的副本，不影响ao，python传的是引用
        return self.ao[:]

    def getresult(self,wordids,urlids):
        self.setupnetwork(wordids,urlids)
        return self.feedforward()

    #函数在解近输出1,-1时变化率小
    #用1.0-y*y来近似斜率，可以反应斜率变化关系

    def backPropagate(self,targets,N=0.5):

        output_deltas=[0.0]*len(self.urlids)

        for k in range(len(self.urlids)):
            error= targets[k]-self.ao[k]

            #目标节点所需要的改变量=方向×变化率
            output_deltas[k] = dtanh(self.ao[k]) * error

            hidden_deltas=[0.0]*len(self.hiddenids)

            for j in range(len(self.hiddenids)):
                error=0.0

                for k in range(len(self.urlids)):
                    error+=output_deltas[k]*self.wo[j][k]

                #输出大小决定变化率：（一次改变多少）
                hidden_deltas[j]=dtanh(self.ah[j]) * error
        # update output weights
        for j in range(len(self.hiddenids)):
            for k in range(len(self.urlids)):
                change = output_deltas[k]*self.ah[j]
                self.wo[j][k] = self.wo[j][k] + N*change

        # update input weights
        for i in range(len(self.wordids)):
            for j in range(len(self.hiddenids)):
                change = hidden_deltas[j]*self.ai[i]
                self.wi[i][j] = self.wi[i][j] + N*change


    def trainquery(self,wordids,urlids,selectedurl):
        self.generatehiddennode(wordids,urlids)

        self.setupnetwork(wordids,urlids)
        self.feedforward()

        #targets实际用户点击数据
        targets=[0.0]*len(urlids)
        targets[urlids.index(selectedurl)] = 1.0

        self.backPropagate(targets)
        self.updatedatabase()

    def updatedatabase(self):
      # set them to database values
      for i in range(len(self.wordids)):
          for j in range(len(self.hiddenids)):
              self.setstrength(self.wordids[i],self. hiddenids[j],0,self.wi[i][j])
      for j in range(len(self.hiddenids)):
          for k in range(len(self.urlids)):
              self.setstrength(self.hiddenids[j],self.urlids[k],1,self.wo[j][k])
      self.con.commit() 

if __name__ == '__main__':

    mynet=searchnet('nn.db')
    #mynet.maketables()

    w,r,b = 101,102,103
    W,R,E = 201,202,203

    mynet.trainquery([w,b],[W,R,E],E)

    #mynet.generatehiddennode([w,b],[W,R,E])
    #mynet.generatehiddennode([w,r,b],[W,R])
    print mynet.getresult([w,b],[W,R,E])
















                












