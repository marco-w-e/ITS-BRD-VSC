import tkinter as tk


class TrafficLight(tk.Canvas):
    # Creates a red / green traffic light
    def __init__(self, master):
        tk.Canvas.__init__(self, master, width=20, height=20, background='white', highlightthickness=0)
        self.oval_in_canvas = self.create_oval(5, 5, 18, 18, fill='green')

    def set(self, color):
        self.itemconfigure(self.oval_in_canvas, fill=color)
