#-*-coding:utf8-*-

from Tkinter import *

root=Tk()

v=[]
GIRLS=['a','b','c','d']
for g in GIRLS:
    v.append(IntVar())
    #Checkbutton
    b=Checkbutton(root,text=g,variable=v[-1]) 
    b.pack()


mainloop()
