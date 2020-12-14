from Tkinter import *

root=Tk()
e=Entry(root)
e.pack(padx=20,pady=29)

e.delete(0,END)
e.insert(0,'...')

mainloop()
