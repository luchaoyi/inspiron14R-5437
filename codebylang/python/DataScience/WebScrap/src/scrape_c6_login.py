#coding:utf8

import lxml.html
import urllib,urllib2

LOGIN_URL="http://example.webscraping.com/user/login"
LOGIN_EMAIL="qaz123wsx@qq.com"
LOGIN_PASSWORD="123456"


def parse_html(html):
    tree=lxml.html.fromstring(html)
    data={}
    #print tree.cssselect('form input')
    for e in tree.cssselect('form input'): #form标签 中 input标签(按钮) 
        if e.get('name'):
            data[e.get('name')]=e.get('value') 
    return data


def demo0():
    import pprint 
    html=urllib2.urlopen(LOGIN_URL).read()
    #print html
    form=parse_html(html)
    pprint.pprint(form)



def demo1():
    html=urllib2.urlopen(LOGIN_URL).read()
    data=parse_html(html)
    data['email']=LOGIN_EMAIL
    data['password']=LOGIN_PASSWORD
    encode_data=urllib.urlencode(data) #设置<from enctype=application/x-www-form-urlencode
    #print encode_data 
    request=urllib2.Request(LOGIN_URL,encode_data)
    response=urllib2.urlopen(request)
    print response.geturl()
    #登录失败，_formkey会保存在cookie中
    #cookie:由服务器生成，服务器和浏览器都会保存，浏览器将这些数据包含在后续请求头中，让服务器跟踪识别用户

def demo2():
    import cookielib
    cj=cookielib.CookieJar()
    opener=urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
    #html=urllib2.urlopen(LOGIN_URL).read()
    html=opener.open(LOGIN_URL).read() #第一次打开将 _formkey保存在cookie中
    #print cj

    data=parse_html(html)
    data['email']=LOGIN_EMAIL
    data['password']=LOGIN_PASSWORD
    encode_data=urllib.urlencode(data) #设置<from enctype=application/x-www-form-urlencode
    request=urllib2.Request(LOGIN_URL,encode_data)

    #response=urllib2.urlopen(request)
    response=opener.open(request) #再次请求时包含cookie数据
    print response.geturl()

    #此时使用opener.open可以打开登录后的页面，因为cookie跟踪它为已登录状态
    print opener.open(response.geturl()).read()#登录后获取此url的页面





#从浏览器提取cookie
#先使用浏览器登录，然后在浏览器存储路径，提取cookie.
#如Firefox在sqlite中存储cookie,在JSON中存储session,这两种存储Python都可以获取
#不同系统，浏览器存储方式，路径等不同.

#Mechanize更高级的模块可以创建一个浏览器对象，自动管理cookie

if __name__ == "__main__":
    #demo0()
    """
    result={
    demo0运行结果，登录表单包含的内容
 '_formkey': 'c4f8a181-d40f-4cb1-a1bd-31770d58fdb9', #加载网页时产生一个ID,用ID可以判断表单是否已经提交过
 '_formname': 'login',
 '_next': '/',
 'email': '',
 'password': '',
 'remember_me': 'on'}"""
    #demo1()
    demo2()



