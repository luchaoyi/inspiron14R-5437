#!coding:utf8
from Tkinter import *

root=Tk()

#5*30
text=Text(root,width=30,height=5)
text.pack()

text.insert(INSERT,'l\n')
text.insert(END,'y')

#text中可以插入文本，组件，图片等

mainloop()
