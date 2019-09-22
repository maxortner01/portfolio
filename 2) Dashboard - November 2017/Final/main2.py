from tkinter import Tk, Frame, Entry, Label, Listbox, END, Checkbutton, IntVar, Toplevel, StringVar, Menu, Toplevel
from ttk import Button, Combobox
from modules.patch import patchGame as pg
from bin.dashes.editor.editor import dashEditor
from bin.dashes.client.raceclient import window
import sys, json, psutil, os
import tkFileDialog as dialog
import tkMessageBox as msgbox

def launchDash(dash):
    if dash == "BRZ":
        b = BRZ.dashboard(1920, 1080)
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
            self.data = {'patched': [], 'supported-games': ['assettocorsa.exe', 'pcars2.exe', 'pcars2avx.exe', 'dirt4.exe'], 'odometer': {'GT_Motorsport': 0}, 'alwaysopen': 0}

        menubar = Menu(self.master)
        filemenu = Menu(menubar, tearoff=0)
        filemenu.add_command(label='New Dash...', command=self.newDash)
        filemenu.add_separator()
        filemenu.add_command(label='Race Client...', command=self.raceClient)

        menubar.add_cascade(label='File', menu=filemenu)

        self.master.config(menu=menubar)

        self.clientOpen = False

        self.top = Frame(self.master)
        self.top.pack(fill='both', expand=True, pady=5)

        self.middle = Frame(self.master)
        self.middle.pack(fill='both', expand=True)

        self.bottom = Frame(self.master)
        self.bottom.pack(fill='both', expand=True)

        #BOTTOM
        self.bottombottom = Frame(self.bottom)
        self.bottombottom.pack(fill='x', expand=True)

        self.launchda = Button(self.bottombottom, text="Launch Dashboard", command=lambda: self.launchD(1920, 1080))
        self.launchda.pack(side='left', fill='x', expand=True)

        self.colorval = StringVar()
        self.color = Combobox(self.bottombottom, textvariable=self.colorval)
        self.color.pack(side='left', fill='x', expand=True, anchor='center')

        self.game = Label(self.bottom, text='No Game Running')
        self.game.pack(fill='x', expand=True, anchor='center')

        self.currentdash = Label(self.bottom, text="Current Dash:\n")
        self.currentdash.pack(fill='x', expand=True, anchor='n', padx=10)


        #TOP
        self.patch = Button(self.top, text="Patch a Game", command=self.patchGame)
        self.patch.pack(side='left', fill='x', expand=True, anchor='n', padx=10)

        sv = StringVar()
        sv.trace("w", lambda name, index, mode, sv=sv: self.callback(sv))
        self.search = Entry(self.top, textvariable=sv)
        self.search.pack(side='right', fill='x', padx=10)
        self.sv = sv

        self.search.bind('<FocusIn>', lambda x: self.on_entry_click())
        self.search.bind('<FocusOut>', lambda x: self.on_focusout())
        self.on_focusout()
        #MIDDLE
        self.patched = Listbox(self.middle)
        self.patched.pack(side='left', fill='x', expand=True, anchor='n', padx=10)

        self.dashes = Listbox(self.middle)
        self.dashes.pack(side='left', fill='both', expand=True, padx=10)

        for item in self.data['patched']:
            self.patched.insert(END, item.split("/")[len(item.split("/")) - 1])

        setas = []
        for f in os.listdir(self.path + "/bin/dashes"):
            if "." in f and f.split('.')[1] == 'py':
                if f.split('.')[0] == '__init__':
                    continue

                self.dashes.insert(0, f.split('.')[0].replace("_", " "))
                setas.append(f.split('.')[0].replace("_", " "))

        self.dashes.bind('<Double-1>', lambda x: self.selected())

        self.setas = setas
        self.currentd = setas[0]

        self.master.protocol('WM_DELETE_WINDOW', self.onClose)
        self.runningGame = ''
        self.hasrun = False

        self.setcolors()

        self.isGame()

    def raceClient(self):
        if not self.clientOpen:
            window(self.master)

    def newDash(self):
        dashEditor(1280, 720, self.path).execute()

    def setcolors(self):
        self.color['values'] = ()
        if self.currentd == 'GT Legacy':
            self.color['values'] = ("Classic")
            self.color.set("Classic")
        else:
            self.color['values'] = ("Dark", "Light")
            self.color.set("Dark")

    def selected(self):
        self.currentd = self.dashes.selection_get()
        self.currentdash.config(text="Current Dash:\n" + self.dashes.selection_get())

    def callback(self, sv):
        if sv.get() == 'Search...':
            return
        newlist = []
        for x in self.setas:
            for y in x.split(" "):
                if y.lower()[:len(sv.get().lower())] == sv.get().lower() or sv.get().lower() == x.lower()[:len(sv.get().lower())]:
                    newlist.append(x)

        self.dashes.delete(0, END)
        done = []
        for x in newlist:
            if not x in done:
                self.dashes.insert(0, x)
                done.append(x)

    def on_entry_click(self):
        """function that gets called whenever entry is clicked"""
        if self.sv.get() == 'Search...':
            self.search.delete(0, "end") # delete all the text in the entry
            self.search.insert(0, '') #Insert blank for user input
            self.search.config(fg = 'black')
    def on_focusout(self):
        if self.sv.get() == '':
            self.search.insert(0, 'Search...')
            self.search.config(fg = 'grey')

    def checked(self):
        self.data['alwaysopen'] = int(self.var.get())
        f = open('bin/data.txt', 'w')
        f.write(json.dumps(self.data, indent=4))
        f.close()

    def launchD(self, a, y, color='Dark'):
        from bin.dashes import GT_Motorsport, GT_Legacy
        color = self.colorval.get()

        if len(self.runningGame) > 0 and not self.clientOpen:
            for x in self.data['patched']:
                if x.split('/')[len(x.split('/')) - 1] == self.runningGame:
                    b = eval(self.currentd.replace(" ", "_")).dashboard(a, y, x, e=color)
                    b.execute()
        elif self.clientOpen:
            msgbox.showwarning("Race Client", 'Race Client must be closed.')
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
            self.currentdash.config(text='Current Dash:\n' + self.currentd)
            self.setcolors()
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

            fo = False
            for id in self.master.children:
                if str(self.master.children[id].winfo_name.im_class).lower() == 'tkinter.toplevel':
                    fo = True

            if fo:
                self.clientOpen = True
            else:
                self.clientOpen = False

            self.master.update_idletasks()
            self.master.update()
            #self.master.after(1, self.isGame)






if __name__ == '__main__':
    root = Tk()
    gui = main(root)
    root.mainloop()
