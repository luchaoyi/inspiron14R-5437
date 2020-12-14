#!coding:utf8

import urllib2
import re

#URl Error 
#4xx  表示请求出现错误,如404 Not Found
#5xx  表示服务器端出现错误，如503 服务器过载,5xx可以retries


def download0(url,num_retries=1):
    print "Downloading:",url 
    try:
        html=urllib2.urlopen(url).read()
    except urllib2.URLError as e:
        print 'Downloading error:',e.reason
        html=None
        #5xx可以重试下载过程
        if num_retries>0:
            #有定义e.code 5xx
            if hasattr(e,'code') and 500<=e.code<=600:
                return download0(url,num_retries-1)
    return html

#设置用户代理,默认代理可能被封禁
def download1(url,user_agent='lcy',num_retries=1):
    print "Downloading:",url
    headers={'User-agent':user_agent}
    request=urllib2.Request(url,headers=headers)#生成加入头部信息的浏览器请求
    #print request
    try:
        html=urllib2.urlopen(request).read()
    except urllib2.URLError as e:
        print 'Downloading error:',e.reason
        html=None
        #5xx可以重试下载过程
        if num_retries>0:
            #有定义e.code 5xx 
            if hasattr(e,'code') and 500<=e.code<=600:
                return download1(url,user_agent,num_retries-1)
    return html

#网站地图爬虫,根据sitemap爬取网站
def crawl_sitemap(url):
    sitemap=download1(url)
    links=re.findall('<loc>(.*?)</loc>',sitemap)
    #print links

    for link in links:
        html=download1(link)
        #...

#链接爬虫,广度or深度优先遍历
#链接互相包含时，即有环图，会出现重复，因此需要记录已访问站点，避免循环往复

import urlparse #构建绝对路径
import robotparser #解析robots.txt

def link_crawler(seed_url,link_regex,user_agent='lcy'):
    crawl_queue=[seed_url]
    seen=set(crawl_queue) #记录见到过的url


    rp=robotparser.RobotFileParser()
    rp.set_url(seed_url)
    rp.read()
    while crawl_queue:
        url=crawl_queue.pop()
        if rp.can_fetch(user_agent,url): #解析robots文件,判断代理是否可以访问
            html=download1(url,user_agent)
            #get_links解析出html中所有的静态url
            #link_regex是目标url，过滤掉非目标页面
            for link in get_links(html):
                #print link_regex
                if re.match(link_regex,link):
                    #网页中的href使用的是相对链接路径时，浏览器可以正常访问，但urllib2不能
                    #使用urljoin生成绝对链接路径
                    link=urlparse.urljoin(seed_url,link)
                    if link not in seen:
                        seen.add(link)
                        crawl_queue.append(link)
        else:
            print 'Blocked by robots.txt:',url



def get_links(html):
    webpage_regex=re.compile('<a[^>]+href=["\'](.*?)["\']',re.IGNORECASE)
    return webpage_regex.findall(html)


#下载限速,速度过快会拖累服务器，可能会被禁止
#两次下载直接添加延时来限速.
#记录上次访问域名时间，与延迟时间比较决定延迟时间
class Throttle:
    def __init__(self,delay):
        self.delay=delay
        self.domains={}
    def wait(self,url):
        domain=urlparse.urlparse(url).netloc
        last_accessed=self.domains.get(domain)

        if self.delay>0 and last_accessed is not None:
            sleep_secs=self.delay-(datetime.datetime.now()- last_accessed).seconds
            if sleep_secs>0:
                time.sleep(sleep_secs)
        self.domains[domain]=datetime.datetime.now()

#爬虫设置max_depth可以避免爬虫陷阱
#爬虫陷阱:网页动态生成无穷无尽
#解析链接时记录链接深度，到最大指定深度时不在此节点提取链接
def link_crawler1(seed_url,link_regex,user_agent='lcy',max_depth=2):
    crawl_queue=[seed_url]
    seen={}  #记录见到过的url
    seen[seed_url]=1


    rp=robotparser.RobotFileParser()
    rp.set_url(seed_url)
    rp.read()

    while crawl_queue:
        url=crawl_queue.pop()

        if rp.can_fetch(user_agent,url): #解析robots文件,判断代理是否可以访问
            html=download1(url,user_agent)
            #get_links解析出html中所有的静态url
            #link_regex是目标url，过滤掉非目标页面

            #未达到指定深度则提取links
            depth=seen[url]
            if depth!=max_depth: #令max_depth=负数，则永远不等，则屏蔽了深度限制
                for link in get_links(html):
                    if re.match(link_regex,link):
                        #网页中的href使用的是相对链接路径时，浏览器可以正常访问，但urllib2不能
                        #使用urljoin生成绝对链接路径
                        link=urlparse.urljoin(seed_url,link)
                        if link not in seen:
                            seen[link]=depth+1
                            crawl_queue.append(link)
        else:
            print 'Blocked by robots.txt:',url

if __name__=="__main__":
    #try 1 time,retry 1 time
    #download0('http://httpstat.us/500')
    #download1('http://www.baidu.com')
    #crawl_sitemap('http://example.webscraping.com/sitemap.xml')
    #link_crawler('http://example.webscraping.com','/(index|view)')
    #link_crawler1('http://example.webscraping.com','/(index|view)',max_depth=2)
    link_crawler1('http://www.baidu.com','',max_depth=-1)
    


