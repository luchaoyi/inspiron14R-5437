#-*-coding:utf8-*-

from Tkinter import *



def callback():
    var.set("我不信！！！")


root = Tk()

#frame，都是同一层
frame1=Frame(root)
frame2=Frame(root)


#Label组件用于显示信息，可以显示图片，文字
#justify 调整版面

var=StringVar()
var.set("18×××!!!")
#显示设置为变量可以改变
textLabel=Label(frame1,textvariable=var,justify=LEFT,padx=10)
textLabel.pack(side=LEFT)

photo=PhotoImage(file="18.gif")
imageLabel=Label(frame1,image=photo)
imageLabel.pack(side=RIGHT)

bgphoto=PhotoImage(file="bg.gif")

#Label图片为背景显示文字，图字混合
theLabel = Label(frame1,text="python\nTkinter",
        image=bgphoto,
        compound=CENTER,
        font=("华康少女字体",20),
        fg="white")

theLabel.pack()

theButton=Button(frame2,text="已满18",command=callback)
#Button接收动作
theButton.pack()

frame1.pack()
frame2.pack()



root.mainloop()

