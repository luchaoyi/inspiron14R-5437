#-*-coding:utf8-*-
import Tkinter as tk;

class APP:
    def __init__(self,master):
        #框架是在复杂的window布局中将界面组件分组的
        fram = tk.Frame(master) 

        #pack自动调整位置
        fram.pack(side=tk.LEFT,padx=10,pady=10)

        #现在组件root window成为了Frame 
        #Frame是在根窗口中生长出来的子窗口对象
        #以组件为单位绑定动作响应函数
        #background bg foreground fg
        self.hi_there = tk.Button(fram,text="打招呼",bg='black',fg='blue', \
                command=self.say_hi)
        self.hi_there.pack()

    def say_hi(self):
        print "Hi,World!"
        
root = tk.Tk()
app = APP(root)

root.mainloop()


