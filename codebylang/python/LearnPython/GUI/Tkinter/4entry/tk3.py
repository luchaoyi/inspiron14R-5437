#coding:utf8

#pack
#grid,以表格形式管理组件

from Tkinter import *
root=Tk() 
#指定组件行列
Label(root,text="Id").grid(row=0,column=0)
Label(root,text="Password").grid(row=1,column=0)

v1=StringVar()
v2=StringVar()


#Entry组件具有验证功能选项，可以指定开启验证动作，验证回调函数，以及验证False处理函数
e1=Entry(root,textvariable=v1)
#输入在输入框中以*显示
e2=Entry(root,textvariable=v2,show='*')

e1.grid(row=0,column=1,padx=10,pady=5)
e2.grid(row=1,column=1,padx=10,pady=5)


def show():
    
    #print "%s" % e1.get()
    #print "%s" % e2.get()
    print v1.get()
    print v2.get()


Button(root,text="get",command=show)\
        .grid(row=3,column=0,sticky=W,padx=10,pady=5)
Button(root,text="exit",command=root.quit)\
        .grid(row=3,column=1,sticky=E,padx=10,pady=5)

mainloop()


