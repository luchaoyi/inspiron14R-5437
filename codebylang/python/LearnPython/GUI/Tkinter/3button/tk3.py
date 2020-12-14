#-*-coding:utf8-*-
from Tkinter import *
root=Tk()
v=IntVar()


#select status 则v<=value
Radiobutton(root,text="one",variable=v,value=1).pack(anchor='w')
Radiobutton(root,text="two",variable=v,value=2).pack(anchor='w')
Radiobutton(root,text="three",variable=v,value=3).pack(anchor='w')

mainloop()
