#-*-coding:utf8-*-
import Tkinter as tk 



#1.draw window
#root window
app = tk.Tk()
app.title("lcy demo")

#The root window of Label window  is app 
theLabel = tk.Label(app,text="second window")
theLabel.pack()




#2.message loop
#enter message loop --> callback status
app.mainloop()
