from tkinter import Tk, Frame, Entry, Label, Listbox, END, Checkbutton, IntVar, Toplevel, StringVar
from ttk import Button, Combobox
from modules.patch import patchGame as pg
import sys, json, psutil, os
import tkFileDialog as dialog
import tkMessageBox as msgbox

def launchDash(dash):
    if dash == "BRZ":
        b = BRZ.dashboard(1280, 720)
        b.execute()

class main:
    def __init__(self, master):
        self.master = master
        self.path = "/".join(os.path.dirname(os.path.realpath(__file__)).split('\\')) + '/'

        try:
            self.data = json.loads(open('bin/data.txt', 'r').read())
            if len(self.data) == 0:
                raise ValueError('1')
        except:
            self.data = {'patched': [], 'supported-games': ['assettocorsa.exe', 'pcars2.exe', 'pcars2avx.exe', 'dirt4.exe'], 'odometer': {'BRZ': 0}, 'alwaysopen': 0}

        self.toptop = Frame(self.master)
        self.toptop.pack(fill='x', expand=True, anchor='n')

        self.game = Label(self.toptop, text='No Game Running!')
        self.game.pack(fill='x', expand=True, anchor='ne')

        self.top = Frame(self.master)
        self.top.pack(fill='x', expand=True, anchor='n')

        self.patch = Button(self.top, text='Patch a Game', command=self.patchGame)
        self.patch.pack(side='left', fill='x', expand=True, padx=5, anchor='n')

        self.minimizeb = Button(self.top, text='-', command=lambda: self.minimize('patch'))
        self.minimizeb.pack(side='left', fill='x', expand=True, anchor='n')

        self.patched = Listbox(self.top)
        self.patched.pack(fill='both', expand=True, padx=5, anchor='n')

        self.dashval = StringVar()
        self.dash = Combobox(self.master, textvariable=self.dashval)
        self.dash.pack(fill='x', expand=True, padx=5, anchor='n')
        setas = []
        for f in os.listdir(self.path + "/bin/dashes"):
            if "." in f and f.split('.')[1] == 'py':
                if f.split('.')[0] == '__init__':
                    continue
                setas.append(f.split('.')[0].replace("_", " "))
        self.dash['values'] = setas
        self.dash.set(setas[0])

        self.bottom = Frame(self.master)
        self.bottom.pack(fill='x', expand=True, padx=5, anchor='n')

        self.launch = Button(self.bottom, text='Launch Dash', command=lambda: self.launchD(1280, 720))
        self.launch.pack(side='left', fill='x', expand=True, padx=5, anchor='n')

        self.colorval = StringVar()
        self.color = Combobox(self.bottom, textvariable=self.colorval)
        self.color.pack(side='left', fill='x', expand=True, padx=5, anchor='n')
        self.color['values'] = ('Dark', 'Light')
        self.color.set('Dark')

        self.var = IntVar()
        self.var.set(self.data['alwaysopen'])
        self.openalways = Checkbutton(self.master, text='open dash when game opens', variable=self.var, command=self.checked)
        self.openalways.pack(fill='x', expand=True, padx=5, anchor='n')

        for item in self.data['patched']:
            self.patched.insert(END, item.split("/")[len(item.split("/")) - 1])

        self.master.protocol('WM_DELETE_WINDOW', self.onClose)
        self.runningGame = ''
        self.hasrun = False
        self.isGame()

    def minimize(self, area):
        if area == 'patch':
            text = self.minimizeb['text']
            if text == '+':
                self.minimizeb.config(text='-')
            else:
                self.minimizeb.config(text='+')

    def checked(self):
        self.data['alwaysopen'] = int(self.var.get())
        f = open('bin/data.txt', 'w')
        f.write(json.dumps(self.data, indent=4))
        f.close()

    def launchD(self, a, y, color='Dark'):
        from bin.dashes import GT_Motorsport, GT_Legacy
        color = self.colorval.get()

        if len(self.runningGame) > 0:
            for x in self.data['patched']:
                if x.split('/')[len(x.split('/')) - 1] == self.runningGame:
                    b = eval(self.dash.get().replace(" ", "_")).dashboard(a, y, x, e=color)
                    b.execute()
        else:
            msgbox.showwarning("Dashboard", 'A game must be running to initiate the dashboard.')

    def onClose(self):
        open(self.path + 'bin/data.txt', 'w').write(json.dumps(self.data, indent=4))
        print "Save files"
        self.master.destroy()
        sys.exit()


    def updateList(self):
        self.patched.delete(0, END)
        for item in self.data['patched']:
            self.patched.insert(END, item.split("/")[len(item.split("/")) - 1])

    def patchGame(self):
        filename = dialog.askopenfilename(title='Select File', filetypes = (("Executables","*.exe"),("all files","*.*")))
        if filename.split("/")[len(filename.split("/")) - 1].lower() in self.data['supported-games']:
            pg(filename)
            if filename.split("/")[len(filename.split("/")) - 1].lower() == 'pcars2.exe' or filename.split("/")[len(filename.split("/")) - 1].lower() == 'pcars2avx.exe':
                self.data['patched'].append('pCARS2.exe')
                self.data['patched'].append('pCARS2AVX.exe')
            else:
                self.data['patched'].append(filename)

            open(self.path + 'bin/data.txt', 'w').write(json.dumps(self.data, indent=4))
            self.updateList()
        else:
            msgbox.showerror('Error', 'Game not supported.')

    def isGame(self):
        while True:
            running = False
            for x in self.patched.get(0, END):
                running = x in (p.name() for p in psutil.process_iter())
                if running:
                    break
                self.master.update_idletasks()
                self.master.update()

            try:
                if json.loads(open(self.path + 'bin/data.txt', 'r').read()) != self.data:
                    self.data = json.loads(open('bin/data.txt', 'r').read())
            except:
                open('bin/data.txt', 'w').write(json.dumps(self.data))

            self.master.update_idletasks()
            self.master.update()
            if running:
                self.runningGame = x
                self.game.config(text=self.runningGame)
                if self.data['alwaysopen'] == 1 and self.hasrun == False:
                    self.hasrun = True
                    self.launchD(1920, 1080)
            else:
                self.master.update_idletasks()
                self.master.update()
                self.hasrun = False
                self.runningGame = ''
                self.game.config(text='No Game Running')

            self.master.update_idletasks()
            self.master.update()
            #self.master.after(1, self.isGame)


if __name__ == '__main__':
    root = Tk()
    gui = main(root)
    root.mainloop()
