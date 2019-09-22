import matplotlib
from tkinter import Tk, Frame, Toplevel, Label
from ttk import Labelframe

class window:
    def __init__(self, master):
        t = Toplevel(master)
        t.wm_title('Race Client')

        self.runningGame = Label(t, text='No Game Running')

        self.pedals = Labelframe(t, text='Pedal Information')
        self.pedals.pack(fill='both', expand=True)
