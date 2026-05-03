"""
   A tk string variable that stores every string.
   But during a get method call the value of the string var will be validated.
   An invalid string value generates a ValueError exceptions.
"""
import tkinter as tk


class MyStringVar(tk.StringVar):
    def __init__(self, check_func, value=""):
        self.check = check_func
        tk.StringVar.__init__(self, value=value)

    def get(self):
        return self.check(tk.StringVar.get(self))
