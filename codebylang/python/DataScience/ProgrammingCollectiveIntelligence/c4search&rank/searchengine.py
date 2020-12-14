#!/usr/bin/python 
#-*-coding:utf8-*-

import urllib2
import sqlite3
import re 
from bs4 import *
from urlparse import urljoin

import nn


#停止词

ignorewords=set(['the','of','to','and','a','in','is','it'])        

class crawler:
    
    def __init__(self,dbname): 
        self.con=sqlite3.connect(dbname)

    def __del__(self):
        self.con.close()

    def dbcommit(self):
        self.con.commit()

    def getentryid(self,table,field,value,createnew=True):
        cur=self.con.execute(
                    "select rowid from %s where %s='%s'" % (table,field,value))
        res=cur.fetchone()

        if res==None:
            cur=self.con.execute("insert into %s (%s) values ('%s')" % (table,field,value))
            return cur.lastrowid
        else:
            return res[0]


    
    #word table url table  url<-->word location table
    def addtoindex(self,url,soup):
        if self.isindexed(url): print 'Indexing'+url

        #get text and split word
        text=self.gettextonly(soup)
        words=self.separatewords(text)

        #from urllist get url id if not insert then insert return id else return id
        urlid=self.getentryid('urllist','url',url)

        #处理每一个单词加入db 
        for i in range (len(words)):
            word=words[i]
            if word in ignorewords:continue
            wordid=self.getentryid('wordlist','word',word)

            self.con.execute("insert into wordlocation(urlid,wordid,location) values (%d,%d,%d)" % (urlid,wordid,i))

    def gettextonly(self,soup):
        v=soup.string
        if v==None:
            c=soup.contents
            resulttext=''
            #多个字节点，递归解析
            for t in c:
                subtext=self.gettextonly(t)
                resulttext+=subtext+'\n'
            return resulttext
        else:
            return v.strip()

    def separatewords(self,text):
        #加r代表原生字符串
        splitter=re.compile('\\W*')
        return [s.lower() for s in splitter.split(text) if s!=''] 


    #table 行：记录 列：字段
    def isindexed(self,url):
        #默认有 rowid 字段(列)
        u=self.con.execute("select rowid from urllist where url='%s'" %url).fetchone()

        #网页是否有记录
        if u!=None:
            #是否有单词与之关联
            v=self.con.execute('select * from wordlocation where urlid=%d' %u[0]).fetchone()
            if v!=None: return True

        return False


    def addlinkref(self,urlFrom,urlTo,linkText):
        words=self.separatewords(linkText)

        fromid=self.getentryid('urllist','url',urlFrom)
        toid=self.getentryid('urllist','url',urlTo)

        if  fromid == toid: return
        cur=self.con.execute("insert into link(fromid,toid) values (%d,%d)" % (fromid,toid))
        linkid=cur.lastrowid

        for word in words:
            if word in ignorewords:continue
            wordid=self.getentryid('wordlist','word',word)
            self.con.execute("insert into linkwords(linkid,wordid) values (%d,%d)" %(linkid,wordid))


    #广度优先遍历(层序遍历)
    #pages是初始url列表
    def crawl(self,pages,depth=2):
        for i in range(depth):
            newpages=set()

            for page in pages:
                try:
                    c=urllib2.urlopen(page)

                #安全软件到处都是异常处理
                except:
                    print "Could ont open %s" % page
                    continue
                soup=BeautifulSoup(c.read())

                #建立索引
                self.addtoindex(page,soup)


                links=soup('a')

                #处理url
                for link in links:
                    #<a 的每一行检查是否有 href属性
                    if('href' in dict(link.attrs)):
                        #urljoin将url相对路径转化为绝对路径
                        url=urljoin(page,link['href'])
                        if url.find("'") != -1 : continue 
                        url=url.split('#')[0] #去掉位置部分 #在网页中用于浏览器定位对于http没有用
                        #是否正确的url 是否索引过避免重复
                        if url[0:4] == 'http' and not self.isindexed(url):
                            newpages.add(url)
                        
                        linkText=self.gettextonly(link)
                        self.addlinkref(page,url,linkText)

                self.dbcommit()

            pages=newpages


     # Create the database tables
    def createindextables(self): 
        self.con.execute('create table urllist(url)')
        self.con.execute('create table wordlist(word)')
        self.con.execute('create table wordlocation(urlid,wordid,location)')
        self.con.execute('create table link(fromid integer,toid integer)')
        self.con.execute('create table linkwords(wordid,linkid)')
        self.con.execute('create index wordidx on wordlist(word)')
        self.con.execute('create index urlidx on urllist(url)')
        self.con.execute('create index wordurlidx on wordlocation(wordid)')
        self.con.execute('create index urltoidx on link(toid)')
        self.con.execute('create index urlfromidx on link(fromid)')
        self.dbcommit()


    def calculatepagerank(self,iterations=20):

        self.con.execute('drop table if exists pagerank')
        self.con.execute('create table pagerank(urlid primary key,score)')


        self.con.execute('insert into pagerank select rowid,1.0 from urllist')
        self.dbcommit()

        for i in range(iterations):
            print "Iterations %d" % (i)
            
            for (urlid,) in self.con.execute('select rowid from urllist'):
                pr=0.15

                #寻找 链接到urlid的所有网页 from-->urlid
                #distinct消除重复的
                for(linker,) in self.con.execute("select distinct fromid from link where toid=%d" %urlid):
                    #计算pagerank 需要找到网页的pagerank和链接数

                    linkingpr=self.con.execute('select score from pagerank where urlid=%d' %linker).fetchone()[0]
                    #此网页总链接数
                    linkingcount=self.con.execute('select count(*) from link where fromid=%d' %linker).fetchone()[0]
                    #总链树中有多少个是链接向此时要计算pagerank的网页
                    linktothiscount=self.con.execute('select count(*) from link where fromid=%d and toid=%d' \
                            %(linker,urlid)).fetchone()[0]

                    pr+=0.85*(linkingpr*linktothiscount/linkingcount)

                self.con.execute(
                        'update pagerank set score=%f where urlid=%d' %(pr,urlid))
            
                self.dbcommit()



class searcher:
    def __init__(self,dbname):
        self.con=sqlite3.connect(dbname)

    def __del__(self):
        self.con.close()
    
    
    #接受查询字符串，返回文档

    def getmatchrows(self,q):
        fieldlist='w0.urlid'
        tablelist=''
        clauselist=''
        wordids=[]

        #根据空格将单词分开
        words=q.split(' ')
        print words
        tablenumber=0

        for word in words:
            #word-->rowid --> word<-->url 
            #url-->rowid-->   ...
            wordrow=self.con.execute("select rowid from wordlist where word='%s'" %word).fetchone()


            if wordrow!=None:
                wordid=wordrow[0]
                wordids.append(wordid)

                if tablenumber>0:
                    tablelist+=','
                    clauselist+=' and '
                    clauselist+='w%d.urlid=w%d.urlid and ' %(tablenumber-1,tablenumber)
                fieldlist+=',w%d.location' % tablenumber
                tablelist+='wordlocation w%d' % tablenumber 
                clauselist+='w%d.wordid=%d' %(tablenumber,wordid)
                tablenumber+=1


        #为单词建立了不同的表引用
        fullquery='select %s from %s where %s' %(fieldlist,tablelist,clauselist)

        print fullquery
        cur=self.con.execute(fullquery)
        rows=[row for row in cur]

        return rows,wordids

    #基于内容排名
    #单词频度：判断相关程度
    #文档位置：主题靠近文档开始
    #单词距离：查询条件有多个单词，则在文档中出现位置靠的很近
    def getscoredlist(self,rows,wordids):
        #文档:分数
        totalscores=dict([(row[0],0) for row in rows])

        mynet=nn.searchnet('nn.db')

        #多种考量方法，加权累计评分
        weights=[(1.0,self.frequencyscore(rows)),
                (1.0,self.locationscore(rows)),
                (1.0,self.distancescore(rows)),
                (1.0,self.inboundlinkscore(rows)),
                (1.0,self.pagerankscore(rows)),
                (1.0,self.linktextscore(rows,wordids)),
                (2,self.nnscore(rows,wordids,mynet))
                ]


        for(weight,scores) in weights:
            for url in totalscores:
                totalscores[url]+=weight*scores[url]

        return totalscores

    def geturlname(self,id):
        return self.con.execute("select url from urllist where rowid=%d" % id).fetchone()[0]

    def query(self,q):

        #寻找所有包含关键字网页
        rows,wordids=self.getmatchrows(q)

        #得分
        scores=self.getscoredlist(rows,wordids)
        #排序
        rankedscores=sorted([(score,url) for (url,score) in scores.items()],reverse=1)

        
        for (score,url) in rankedscores[0:10]:
            print '%f\t%s' % (score,self.geturlname(url))

        #取出返回网页id
        #返回结果，结合实际点击在训练

        #查询，排名,点击，训练，-->迭代
        return wordids,[r[1] for r in rankedscores[0:10]]



    def normalizescores(self,scores,smallIsBetter=0):
        vsmall=0.00001

        if smallIsBetter:

            minsore=min(scores.values())
            return dict([(u,minsore/max(vsmall,l)) for (u,l) in scores.items()])
        else:

            #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            #越大越好--> 0,1 x/MAX 同理 越小越好 -->0,1 MIN/x
            maxscore=max(scores.values())

            if maxscore==0.0:maxscore=vsmall
            return dict([(u,float(c)/maxscore) for (u,c) in scores.items()])

#词频
    def frequencyscore(self,rows):
        counts=dict([(row[0],0) for row in rows])

        #统计文档在返回结果中出现的次数
        #次数越多说明出现单词越多
        for row in rows:counts[row[0]]+=1 
        return self.normalizescores(counts)
#文档位置,越近越好
    def locationscore(self,rows):
        #init
        locations=dict([(row[0],10000) for row in rows])

        for row in rows:
            #考量所有词相加
            loc=sum(row[1:])

            if loc<locations[row[0]]: locations[row[0]]=loc
        #越小越好
        return self.normalizescores(locations,smallIsBetter=1)
    

    def distancescore(self,rows):
        #一个单词 得分相同
        if len(rows[0])<=2: return dict([(row[0],1.0) for row in rows])

        mindistance=dict([(row[0],100000) for row in rows])

        for row in rows:
            dist=sum([abs(row[i]-row[i-1]) for i in range(2,len(row))])

            if dist<mindistance[row[0]]:
                mindistance[row[0]]=dist

        return self.normalizescores(mindistance,smallIsBetter=1)

    #网页被链接越多，重要性越大
    def inboundlinkscore(self,rows):
        uniqueurls=set([row[0] for row in rows])
        inboundcount=dict([(u,self.con.execute( 
                'select count(*) from link where toid=%d' % u).fetchone()[0]) 
                for u in uniqueurls])

        return self.normalizescores(inboundcount)

    def pagerankscore(self,rows):
        pageranks=dict([(row[0],self.con.execute(
            'select score from pagerank where urlid=%d' % row[0]).fetchone()[0] \
                    ) for row in rows])

        maxrank=max(pageranks.values())
        normalizescores=dict([(u,float(l)/maxrank) for (u,l) in pageranks.items()])
        return normalizescores


    #利用链接自身文本信息来决定网页排名,A-->B B的分值考虑A的内容与搜索内容相关
    #与搜索内容相关的网页的pagerank累积为此网页基于内容链接的分数
    #即A，B，C，D--都指向E 一次搜索中 A B C与搜索内容相关 则 E的linktextscore分=pageranks(A+B+C)
    def linktextscore(self,rows,wordids):
        linkscores=dict([(row[0],0) for row in rows])
        for wordid in wordids:
            cur=self.con.execute('select link.fromid,link.toid from linkwords,link where wordid=%d and linkwords.linkid=link.rowid' % wordid)

            #cur，词语a-->link A-->B  a属于A内容
            #但B不一定包含a
            for (fromid,toid) in cur:
                #所以 toid 不一定属于 linkscores,linkscores计算的是所有包含搜索关键字文档的分值
                #所以每个文档都有pagerank(用户点击到此网页的概率),但不一定有linkscore
                if toid in linkscores:
                    pr=self.con.execute('select score from pagerank where urlid=%d' % fromid).fetchone()[0]
                    linkscores[toid]+=pr
        maxscore=max(linkscores.values())
        if maxscore == 0: return linkscores 
        normalizedscores=dict([(u,float(l)/maxscore) for (u,l) in linkscores.items()])
        return normalizedscores

    def nnscore(self,rows,wordids,neuralnet):

        #set中去掉重复的
        urlids=[urlid for urlid in set([row[0] for row in rows])]
        #
        nnres=neuralnet.getresult(wordids,urlids)

        scores=dict([(urlids[i],nnres[i]) for i in range(len(urlids))])

        return self.normalizescores(scores)


if __name__ == '__main__':
    #爬取
    #pagelist=['http://www.twitter-buttons.biz/http/www/kiwitobes.com']
    #cra=crawler('searchindex.db')

    #建表运行一次
    #cra.createindextables() 
    #cra.crawl(pagelist)

    #计算pagerank,通常只在链接更新时运行，运行时间较长，一半在线下
    #cra=crawler('searchindex.db')
    #cra.calculatepagerank()




    #测试检索,返回词id=2的相关文档
    #dbtest=sqlite3.connect('searchindex.db')
    #resultlist=[row for row in dbtest.execute(
    #    'select rowid from wordlocation where wordid=2')]
    #print resultlist
    #dbtest.close()

    
    #测试查询
    #为不同表建立了不同的引用    

    #select w0.urlid,w0.location,w1.location from wordlocation w0,wordlocation w1 where w0.wordid=1 and w0.urlid=w1.urlid and w1.wordid=51
    #sear=searcher('searchindex.db')
    #wordids,urlids=sear.query('html function program public')



    #加入神经网络
    sear=searcher('searchindex.db')
    wordids,urlids=sear.query('function twitter')
    mynet=nn.searchnet('nn.db')
    print urlids
    #click number

    urlid=14
    mynet.trainquery(wordids,urlids,urlid)
