from tkinter import Tk, Label, Frame, Menu, Toplevel, Listbox, END, VERTICAL, Canvas
from ttk import Progressbar, Notebook, Button, Treeview, Entry, Separator
from modules import udp
from modules.data import *
from modules.se import *
from modules.patch import patchGame
from modules.running import verification
import tkMessageBox as msgbox
import tkFileDialog as browse
import re

class App:
    def __init__(self, master):
        self.master = master
        self.u = udp.UDP()
        self.u.open()

        menubar = Menu(self.master)
        self.isgame = False

        filemenu = Menu(menubar)
        filemenu.add_command(label='Map', command=self.mapdraw)
        filemenu.add_command(label='Preferences', command=self.preferences)
        menubar.add_cascade(label='File', menu=filemenu)

        self.master.config(menu=menubar)

        self.prog = Notebook(master)
        self.prog.pack(fill='both', expand=True)
        self.arduinos = {}

        self.telem = Frame(self.prog)
        self.middlebar = Frame(self.telem)
        self.numbers = Frame(self.middlebar)
        self.progs   = Frame(self.middlebar)
        self.topbar  = Frame(self.telem)
        self.bottombar = Frame(self.telem)
        self.gamerunning = Label(self.topbar, text='Game not Running')
        self.searchgame  = Button(self.topbar, text='Start', command= lambda: self.gamesearch())
        self.topbar.pack(anchor='nw', fill='both', expand=True)
        #self.searchgame.pack(side='left', fill='x')
        self.gamerunning.pack(side='right')
        self.middlebar.pack(anchor='nw', fill='x', expand=True)
        self.numbers.pack(side='left', fill='both', expand=True)
        self.progs.pack(side='left', fill='both', expand=True)
        self.bottombar.pack(anchor='n')

        self.arduinos = Frame(self.prog)
        self.rpm = Label(self.numbers, text='rpm: ')
        self.rpm.pack(anchor='nw', expand=True)

        self.rpmbar = Progressbar(self.progs)
        self.rpmbar.pack(anchor='nw', fill='x', pady=5)

        Label(self.progs, text='').pack(anchor='nw')
        self.steerbar = Progressbar(self.progs)
        self.steerbar.pack(anchor='nw', fill='x', pady=5)

        Label(self.progs, text='').pack(anchor='nw')
        self.throttlebar = Progressbar(self.progs)
        self.throttlebar.pack(anchor='nw', fill='x', pady=5)

        self.brakebar = Progressbar(self.progs)
        self.brakebar.pack(anchor='nw', fill='x', pady=5)

        self.clutchbar = Progressbar(self.progs)
        self.clutchbar.pack(anchor='nw', fill='x', pady=5)

        self.backright = Progressbar(self.bottombar, orient=VERTICAL)
        self.backright.pack(side='left', fill='both')

        self.frontright = Progressbar(self.bottombar, orient=VERTICAL)
        self.frontright.pack(side='left', fill='both', padx=10)

        self.frontleft = Progressbar(self.bottombar, orient=VERTICAL)
        self.frontleft.pack(side='left', fill='both', padx=10)

        self.backleft = Progressbar(self.bottombar, orient=VERTICAL)
        self.backleft.pack(side='left', fill='both')


        self.search = Button(self.arduinos, text='Search for Arduinos', command=self.searcharduinos)
        self.search.pack(anchor='nw', fill='x', pady=15)

        self.ardview = Treeview(self.arduinos)
        self.ardview.config(columns=['index', 'id', 'sentval'])
        self.ardview.column('index', width=2, anchor='center')
        self.ardview.heading('index', text='#')
        self.ardview.column('id', width=150, anchor='center')
        self.ardview.heading('id', text='Module ID')
        self.ardview.column('sentval', width=300, anchor='center')
        self.ardview.heading('sentval', text='Value sent to Module')
        self.ardview['show'] = 'headings'
        self.ardview.pack(anchor='n', fill='both', expand=True)


        self.prog.add(self.telem, text='Telemetry')
        self.prog.add(self.arduinos, text='Arduinos')

        self.patchedgames = []
        f = open('bin/patched_games.txt', 'r')
        for line in f:
            self.patchedgames.append(line.strip().split('\\')[len(line.strip().split('\\')) - 1])
        f.close()
        self.runninggame = ""
        self.patchedgamesdir = []

        self.getrpm()

    def mapdraw(self):
        cords = {'x': 0, 'y': 0, 'z': 0}
        def refresh():
            try:
                top.create_line(cords['x'], cords['z'], int(self.u.receive(val='X') / 10), int(self.u.receive(val='Z')/10) + 260)
                cords['x'] = int(self.u.receive(val='X') / 10)
                cords['z'] = int(self.u.receive(val='Z') / 10) + 260
                print str(cords['x']) + ", " + str(cords['z'])
            except Exception as ex:
                print str(ex)
                pass

            self.master.after(5, refresh)

        t = Toplevel()
        t.title('Map')
        t.resizable(width=False, height=False)
        top = Canvas(t, width=500, height=500)
        top.pack()
        refresh()

    def preferences(self):
        def update_listbox():
            l.delete(0, END)
            if len(self.patchedgames) == 0:
                l.insert(END, 'No Games Patched')

            for i in self.patchedgames:
                l.insert(END, i)

        def patch_game(hasloc=False, loc=''):
            if not ":" in str(patchip.get()):
                msgbox.showwarning('Error', 'IP box must be format correctly: "127.0.0.1:20771"')
                return

            if any(c.isalpha() for c in patchip.get()) == True:
                msgbox.showwarning('Error', 'There should be no letters in the IP entry.')
                return

            if not hasloc:
                f = browse.askopenfilename(parent=t, title='Patch a game')
            else:
                f = loc

            if f == None:
                msgbox.showerror('Error', "That file doesn't exist!")
                return


            sgames = []
            g = open('bin/supported_games.txt', 'r')
            for line in g:
                sgames.append(line.strip('\n'))
            g.close()
            if not f.split("/")[len(f.split("/")) - 1] in sgames:
                msgbox.showerror('Error', f.split("/")[len(f.split("/")) - 1] + " is not supported.")
                return
            elif f.split("/")[len(f.split("/")) - 1] in self.patchedgames and patchip.get() == '127.0.0.1:20771':
                msgbox.showwarning('Patched Games', f.split("/")[len(f.split("/")) - 1] + " is already patched.")
                return

            ip   = patchip.get().split(":")[0]
            port = patchip.get().split(":")[1]

            if not patchGame(f, ip, port):
                return
            else:
                msgbox.showinfo('Patched Games', f.split("/")[len(f.split("/")) - 1] + " patched successfully.")
                if not f in self.patchedgames:
                    self.patchedgames.append(f)
                update_listbox()

                f = open('bin/patched_games.txt', 'w')
                f.write("\n".join(self.patchedgames))
                f.close()

                return


        t = Toplevel()
        t.title('Preferences')
        t.resizable(width=False, height=False)
        top = Frame(t)
        bottom = Frame(t)

        patchip = Entry(top)
        patch = Button(top, text="Patch a Game", command=patch_game)
        l = Listbox(bottom)
        update_listbox()


        top.pack(fill='both', expand=True)
        patch.pack(side='left')
        patchip.pack(side='left')
        patchip.insert(0, '127.0.0.1:20771')
        l.pack(fill='both', expand=True)
        Separator(t).pack(fill='x', expand=True)
        bottom.pack(fill='both', expand=True)

    def searcharduinos(self):
        self.master.update()
        self.master.update_idletasks()
        a = Arduino
        arduinos = {}
        for x in serial_ports():
            if a(x).pair(test=True):
                arduinos[a(x).pair()] = a(x).send

        #arduinos = {'rpm': 'asas'}

        if len(arduinos) == 0:
            msgbox.showwarning("Arduinos", 'No arduinos connected!')
        else:
            y = 0
            for x in arduinos:
                self.ardview.insert('', str(y), 'item' + str(y))
                self.ardview.set('item' + str(y), 'index', y)
                self.ardview.set('item' + str(y), 'id', x)
                y = y + 1

            msgbox.showinfo("Arduinos", str(y) + ' module(s) found!')

        self.arduinos = arduinos

    def gamesearch(self):
        if len(self.patchedgames) == 0:
            msgbox.showerror('Patched Games', 'No games have been patched, you must configure your games in the preference menu.')

    def checkgame(self):

        found = False
        for i in self.patchedgames:
            self.master.update_idletasks()
            self.master.update()
            try:
                if verification(i.split("/")[len(i.split("/")) - 1]) == True:
                    found = True
                    break
            except Exception as ex:
                print str(ex)
                return

        print "searched"
        if found == True:
            self.isgame = True
            self.gamerunning.config(text=i)
            self.runninggame = i
        else:
            self.isgame = False
            self.gamerunning.config(text="No game running")
            self.master.update_idletasks()
            self.master.update()

    def getrpm(self):
        game = self.runninggame.lower().split("/")[len(self.runninggame.lower().split("/")) - 1]
        if self.isgame and game == 'dirt4.exe' or game == 'drt.exe':
            if 'None' in self.u.receive():
                self.master.update()
                self.master.update_idletasks()
                self.checkgame()
                self.master.after(1, self.getrpm)
            else:
                try:
                    values = {'backleft': [int(self.u.receive(val='Roll Vector Y') * 100) + 100, (int(self.u.receive(val='Pitch Vector Y') * 100) + 100) * -1 + 200],
                              'backright': [(int(self.u.receive(val='Roll Vector Y') * 100) + 100) * -1 + 200, (int(self.u.receive(val='Pitch Vector Y') * 100) + 100) * -1 + 200],
                              'frontright': [(int(self.u.receive(val='Roll Vector Y') * 100) + 100) * -1 + 200, int(self.u.receive(val='Pitch Vector Y') * 100) + 100],
                              'frontleft': [int(self.u.receive(val='Roll Vector Y') * 100) + 100, int(self.u.receive(val='Pitch Vector Y') * 100) + 100]
                             }
                    tirespeed = [self.u.receive(val='VRear Left'), self.u.receive(val='VRear Right'), self.u.receive(val='VFront Left'), self.u.receive(val='VFront Right')]
                    self.rpmbar.config(maximum=int(self.u.receive(val='Max rpm') * 10), value=int(self.u.receive(val='rpm') * 10))
                    self.steerbar.config(maximum=200, value=int(self.u.receive(val='Steer') * 100) + 100)
                    self.throttlebar.config(maximum=100, value=int(self.u.receive(val='Throttle') * 100))
                    self.brakebar.config(maximum=100, value=int(self.u.receive(val='Brake') * 100))
                    self.clutchbar.config(maximum=100, value=int(self.u.receive(val='Clutch') * 100))

                    self.backleft.config(maximum=200, value=avg(values['backleft']))
                    self.frontleft.config(maximum=200, value=avg(values['frontleft']))

                    self.backright.config(maximum=200, value=avg(values['backright']))
                    self.frontright.config(maximum=200, value=avg(values['frontright']))

                    t =     'rpm:  \t\t' + str(int(self.u.receive(val='rpm') * 10)) + "rpm\n"
                    t = t + 'speed:\t\t' + str(int(self.u.receive(val='Speed')  * 2.23694)) + 'mph\n'
                    if int(avg(tirespeed) * 2.23694) > int(self.u.receive(val='Speed')  * 2.23694) * 1.1:
                        t = t + 'tires:\t\t' + str(int(avg(tirespeed) * 2.23694)) + 'mph  SLIPPING\n'
                    else:
                        t = t + 'tires:\t\t' + str(int(avg(tirespeed) * 2.23694)) + 'mph\n'
                    gear = str(int(self.u.receive(val='Gear')))
                    if gear == '10' or gear == '-1':
                        t = t + 'gear: \t\t' + 'R' + "\n\n"
                    elif gear == '0':
                        t = t + 'gear: \t\t' + 'N' + "\n\n"
                    else:
                        t = t + 'gear: \t\t' + gear + "\n\n"
                    t = t + 'distance:\t\t' + str(self.u.receive(val='Stage Distance') * 0.000621371)[:5] + " miles\n\n"
                    t = t + "Temps:\n"
                    t = t + "BR:\t\t" + str(int(cel_to_far(self.u.receive(val='TBRear Right')))) + "\tF\n"
                    t = t + "BL:\t\t" + str(int(cel_to_far(self.u.receive(val='TBRear Left')))) + "\tF\n"
                    t = t + "FR:\t\t" + str(int(cel_to_far(self.u.receive(val='TBFront Right')))) + "\tF\n"
                    t = t + "FL:\t\t" + str(int(cel_to_far(self.u.receive(val='TBFront Left')))) + "\tF\n"
                    t = t + "\nVectors:\n"
                    t = t + "X:\t\t" + str(self.u.receive(val='Roll Vector Y')) + "\n"
                    t = t + "Y:\t\t" + str(self.u.receive(val='Pitch Vector Y'))
                    self.rpm.config(text=t, justify='left')
                    self.master.update()
                    self.master.update_idletasks()
                    self.checkgame()
                    self.master.after(1, self.getrpm)
                except Exception as ex:
                    print str(ex)
                    self.master.update()
                    self.master.update_idletasks()
                    self.checkgame()
                    self.master.after(1, self.getrpm)
        elif self.isgame and game == 'assettocorsa.exe':
            from modules.assetto import AC
            data = AC(self.runninggame).receive()
            gear = str(data['gear'])
            if gear == '1':
                gear = 'N'
            elif gear == '0':
                gear = 'R'
            else:
                gear = str(int(gear) - 1)

            values = {'backleft': [int(data['roll'] * 1000) + 200, (int(data['pitch'] * 1000) + 200) * -1 + 400],
                      'backright': [(int(data['roll'] * 1000) + 200) * -1 + 400, (int(data['pitch'] * 1000) + 200) * -1 + 400],
                      'frontright': [(int(data['roll'] * 1000) + 200) * -1 + 400, int(data['pitch'] * 1000) + 200],
                      'frontleft': [int(data['roll'] * 1000) + 200, int(data['pitch'] * 1000) + 200]
                     }

            self.backleft.config(maximum=400, value=avg(values['backleft']))
            self.frontleft.config(maximum=400, value=avg(values['frontleft']))

            self.backright.config(maximum=400, value=avg(values['backright']))
            self.frontright.config(maximum=400, value=avg(values['frontright']))

            self.throttlebar.config(maximum=100, value=int(data['throttle'] * 100))
            self.brakebar.config(maximum=100, value=int(data['brake'] * 100))

            t =     'rpm:     \t' + str(data['rpms']) + "rpm\n"
            t = t + 'speed:   \t' + str(int(data['speed'] * 0.621371)) + "mph\n"
            t = t + 'gear:    \t' + gear + '\n\n'
            t = t + 'throttle:\t' + str(data['throttle']) + "\n"
            t = t + 'brake:   \t' + str(data['brake']) + "\n\n"
            t = t + 'Fuel:    \t' + str(data['fuel']) + "/" + str(data['maxFuel']) + '\n'
            t = t + 'Pitch:   \t' + str(int(data['pitch'] * 1000) + 200) + "\n"
            t = t + 'Roll:    \t' + str(int(data['roll'] * 1000) + 200)
            self.rpm.config(text=t, justify='left')
            self.master.update()
            self.master.update_idletasks()
            self.checkgame()
            self.master.after(1, self.getrpm)
        else:
            self.checkgame()
            self.backleft.config(maximum=200, value=0)
            self.frontleft.config(maximum=200, value=0)

            self.backright.config(maximum=200, value=0)
            self.frontright.config(maximum=200, value=0)
            self.rpm.config(text='Start game', justify='left')
            self.master.after(1, self.getrpm)

if __name__ == '__main__':
    root = Tk()
    gui = App(root)
    root.mainloop()
