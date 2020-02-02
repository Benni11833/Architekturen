#!/usr/bin/python3

from tkinter import *
import sys

root = Tk()

root.title('Battery Warning')


var = StringVar()

label = Message(root, textvariable=var, width=600, font=("Arial", 12, "bold"))

text = 'Battery-life critical'
if len(sys.argv) == 2:
    text += f' - {sys.argv[1]}%'
var.set(text)

canvas = Canvas(root, width=600, height=300)

img = PhotoImage(file='/home/benni/battery_warner/low.ppm')
canvas.create_image(0, 0, anchor=NW, image=img)

canvas.pack()
label.pack()
#root.after(10000, root.destroy)
root.mainloop()
