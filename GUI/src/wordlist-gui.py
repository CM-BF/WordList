import tkinter as tk
from tkinter import messagebox
from tkinter.filedialog import *
from ctypes import * 
lib = cdll.LoadLibrary('wordlist.so')


window = tk.Tk()
window.title('WordList')
window.geometry('1000x1000')

"""
Function selection
"""

varwr = tk.IntVar()
varcr = tk.IntVar()
varnc = tk.IntVar()
varhc = tk.IntVar()
vartc = tk.IntVar()
outString = ''
inputFile = ''
preinputFile = ''
inputfromscreen = False

def Choose():
    if varwr.get():
        nc.config(state=tk.DISABLED)
        varnc.set(0)
        varcr.set(0)
        cr.config(state=tk.DISABLED)
    else:
        nc.config(state=tk.NORMAL)
        cr.config(state=tk.NORMAL)
    if varcr.get():
        varwr.set(0)
        wr.config(state=tk.DISABLED)
    else:
        wr.config(state=tk.NORMAL)
    if varnc.get() == 0:
        nt.config(state=tk.DISABLED)
    else:
        nt.config(state=tk.NORMAL)
    if varhc.get() == 0:
        ht.config(state=tk.DISABLED)
    else:
        ht.config(state=tk.NORMAL)
    if vartc.get() == 0:
        tt.config(state=tk.DISABLED)
    else:
        tt.config(state=tk.NORMAL)

def saveFile():
    global outString
    savePath = asksaveasfilename()
    with open(savePath, 'w') as f:
        f.write(outString)

def Click():
    global outString, inputFile
    para_n = nt.get()
    para_h = ht.get()
    para_t = tt.get()
    inputFile = path.get()
    
    if varnc.get() and not para_n.isdigit():
        messagebox.showerror(title='Error', message='Length of words should be a number')
        return
    if varhc.get() and (not para_h.isalpha() or len(para_h) != 1):
        messagebox.showerror(title='Error', message='Head should be a letter')
        return
    if vartc.get() and (not para_t.isalpha() or len(para_t) != 1):
        messagebox.showerror(title='Error', message='Tail should be a letter')
        return
    if varic.get() == 'file' and len(filee.get()) == 0 :
        messagebox.showerror(title='Error', message='Path error')
        return
    if varnc.get() and int(para_n) < 2:
        messagebox.showerror(title='Error', message='Word lengths should >=2')
        return

    if len(para_n)==0:
        para_n = 0
    else:
        para_n = int(para_n)
    if len(para_h) != 1 :
        para_h = '0'
    if len(para_t) != 1 :
        para_t = '0'
    if varcr.get() == 0:
        para_w = True
    else:
        para_w = False

    if varic.get() == 'file':
        #print('in')
        try:
            with open(inputFile, 'r') as f:
                outString = f.read()
            inputfromscreen = False
        except Exception as e:
            print(e)
            messagebox.showerror(title='Error', message='Path error')
            return
    else:
        inputFile = textt.get('1.0', 'end')
        inputfromscreen = True
    count = 0

    if not isinstance(inputFile,bytes) :
        inputFile = inputFile.encode('ascii')
    #print([inputFile,varwr.get(),varhc.get(),para_h,vartc.get(),para_t,varnc.get(),para_n])
    lib.Kana.restype = c_char_p
    outString = lib.Kana(c_char_p(inputFile),c_bool(para_w),c_bool(varhc.get()),c_wchar(para_h), \
        c_bool(vartc.get()),c_wchar(para_t),c_bool(varnc.get()),c_int(para_n),c_bool(inputfromscreen))
    #print(outString)

    outString = outString.decode()
    for i in outString:
        if i == '\n':
            count += 1
    num = 0
    for i in outString:
        if i=='\n':
            break
        else:
            num = num*10 + int(i)
    if num < 1:
        messagebox.showerror(title='Error', message='No wordlists meet the requirements')
        return
    output = tk.Tk()
    output.title('output')
    text = tk.Text(output, height=count, width=10)
    text.insert('end', outString)
    text.pack()
    sb = tk.Button(output, text='Save to..', height=1, width=8, command=saveFile)
    sb.pack()



title = tk.Label(window, text='Functions:').place(x=0, y=0, anchor='nw')
wr = tk.Checkbutton(window, text='Max length of words', variable=varwr, onvalue=1, offvalue=0, command=Choose)
wr.place(x=50, y=50, anchor='nw')
cr = tk.Checkbutton(window, text='Max length of letters', variable=varcr, onvalue=1, offvalue=0, command=Choose)
cr.place(x=50, y=100, anchor='nw')



nc = tk.Checkbutton(window, text='Assign length of words:', variable=varnc, onvalue=1, offvalue=0, command=Choose)
nc.place(x=50, y=150, anchor='nw')
nt = tk.Entry(window, state=tk.DISABLED)
nt.place(x=100, y=200, anchor='nw')

hc = tk.Checkbutton(window, text='Assign head:', variable=varhc, onvalue=1, offvalue=0, command=Choose)
hc.place(x=50, y=250, anchor='nw')
ht = tk.Entry(window, state=tk.DISABLED)
ht.place(x=100, y=300, anchor='nw')

tc = tk.Checkbutton(window, text='Assign tail:', variable=vartc, onvalue=1, offvalue=0, command=Choose)
tc.place(x=50, y=350, anchor='nw')
tt = tk.Entry(window, state=tk.DISABLED)
tt.place(x=100, y=400, anchor='nw')

run_button = tk.Button(window, text='RUN', width=15, height=2, command=Click)
run_button.place(x=700, y=100, anchor='nw')

"""
Words Input
"""
varic = tk.StringVar()
path = tk.StringVar()

def Input():
    if varic.get() == 'file':
        filee.config(state=tk.NORMAL)
        fileb.config(state=tk.NORMAL)
        textt.config(state=tk.DISABLED, background='grey')
    else:
        filee.config(state=tk.DISABLED)
        fileb.config(state=tk.DISABLED)
        textt.config(state=tk.NORMAL, background='white')

def selectPath():
    path_ = askopenfilename()
    path.set(path_)

# file
tk.Label(window, text='Input from:').place(x=50, y=450, anchor='nw')
filec = tk.Radiobutton(window, text='file', variable=varic, value='file', command=Input)
filec.place(x=100, y=500, anchor='nw')
varic.set('file')
filee = tk.Entry(window, textvariable=path)
filee.place(x=250, y=500, anchor='nw')
fileb = tk.Button(window, text='Path..', command=selectPath)
fileb.place(x=600, y=500, anchor='nw')

# textbox
textc = tk.Radiobutton(window, text='text', variable=varic, value='text', command=Input)
textc.place(x=100, y=570, anchor='nw')
textt = tk.Text(window, height=10, width=40, state=tk.DISABLED, background='grey')
textt.place(x=250, y=570, anchor='nw')



window.mainloop()
