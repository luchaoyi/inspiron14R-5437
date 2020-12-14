#-*-coding:utf8-*-

from Tkinter import *

root = Tk()

#Label组件用于显示信息，可以显示图片，文字
#justify 调整版面
textLabel=Label(root,text="18×××\n!!!",justify=LEFT,padx=10)
textLabel.pack(side=LEFT)

photo=PhotoImage(file="18.gif")
imageLabel=Label(root,image=photo)
imageLabel.pack(side=RIGHT)

bgphoto=PhotoImage(file="bg.gif")

#Label图片为背景显示文字，图字混合
theLabel = Label(root,text="python\nTkinter",
        image=bgphoto,
        compound=CENTER,
        font=("华康少女字体",20),
        fg="white")

theLabel.pack()


#Button接收动作


root.mainloop()

