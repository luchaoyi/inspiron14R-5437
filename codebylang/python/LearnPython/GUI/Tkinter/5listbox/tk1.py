#coding:utf8
#滚动条不是一个独立组件
#而是作为一个插件一样，其它组件可以设置安装
from Tkinter import *

master=Tk()

tLB=Listbox(master,selectmode=EXTENDED)
tLB.pack(padx=20,pady=20)


word='abcdefghijklmnopqrstuvwxyz'

for item in word:
    #END末尾cur
    tLB.insert(END,item)


theButton=Button(master,text='删除',command=lambda x=tLB:x.delete(ACTIVE))
theButton.pack()

mainloop()
