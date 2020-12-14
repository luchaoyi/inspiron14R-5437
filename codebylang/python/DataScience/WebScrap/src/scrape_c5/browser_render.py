#coding:utf8

"""

from PyQt4.QtGui import *
from PyQt4.QtCore import *
from PyQt4.QtWebKit import *

url='http://example.webscraping.com/dynamic'

#Qt实现图形界面
app=QApplication([]) #Qt框架必须首先创建该对象
webview=QWebView()   #(浏览器)窗口对象
loop=QEventLoop()    #事件循环对象,创建窗口本地事件循环
webview.loadFinished.connect(loop.quit)
webview.load(QUrl(url)) #下载页面
loop.exec_() #加载异步的，使用loop_exec_()启动事件循环可以等待加载完成后才执行后面的动作

webview.show()
html=str(webview.page().mainFrame().toHtml())#将webview加载的页面转换为html
#html
#Out[47]: '<html><head></head><body>\n        <div id="result">Hello World</div>\n        <script>document.getElementById("result").innerText = 
#\'Hello World\';</script>\n    \n\n</body></html>'
#re.findall('<div id="result">(.*?)</div>',html)
#Out[48]: ['Hello World']
#re.findall('<div id="result">Hello World</div>',html)
#Out[49]: ['<div id="result">Hello World</div>']
app.exec_() #出现窗口，程序执行

"""
