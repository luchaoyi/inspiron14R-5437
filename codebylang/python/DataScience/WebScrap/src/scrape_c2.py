#!coding:utf8

from scrape_c1 import *
import csv
import lxml.html

#提取数据可以采用, re，bs4,lxml.
class ScrapeCallback:
    def __init__(self):
        self.writer = csv.writer(open('countries.csv', 'w'))
        self.fields = ('area', 'population', 'iso', 'country', 'capital', 'continent', 'tld', 'currency_code', 'currency_name', 'phone', 'postal_code_format', 'postal_code_regex', 'languages', 'neighbours')
        self.writer.writerow(self.fields)

    def __call__(self, url, html):
        if re.search('/view/', url):
            tree = lxml.html.fromstring(html)
            row = []
            for field in self.fields:
                row.append(tree.cssselect('table > tr#places_{}__row > td.w2p_fw'.format(field))[0].text_content())
            self.writer.writerow(row)

#为爬虫添加回调函数，处理下载的html中的数据
def link_crawler2(seed_url,link_regex,user_agent='lcy',max_depth=2,scrape_callback=None):
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


            #下载到html后处理数据
            if scrape_callback:
                scrape_callback(url,html)

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
    link_crawler2('http://example.webscraping.com','/(index|view)',max_depth=3,scrape_callback=ScrapeCallback())
    


