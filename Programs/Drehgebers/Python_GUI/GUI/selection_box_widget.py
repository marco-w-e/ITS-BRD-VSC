import tkinter as tk
import tkinter.ttk as ttk
from GUI.help_button_widget import HelpButton
from GUI.my_msg_box_widget import MyMsgBox


class SelectBox:
    """ Simple message box to select an element out of a list"""
    def __init__(self, master, **kwargs):
        self.alt_range = kwargs.pop('alt_range', ["NO ELEMENTS FOR SELECTION"])
        self.action = kwargs.pop('action', lambda w, t: print("Internal Error: No action defined"))
        self.my_box = tk.Toplevel(master)
        self.my_box.configure(background="white")
        self.my_box.title(kwargs.pop('title', " "))
        self.font = ttk.Style().lookup('.', 'font')
        help_button = HelpButton(self.my_box, master, help_text=kwargs.pop('help_text', "No help text"))
        help_button.grid(row=0, column=3, padx=10, pady=10)
        tk.Label(self.my_box, text='   ', bg='white').grid(row=0, column=0)  # define top margin in row 0
        tk.Label(self.my_box, text='   ', bg='white').grid(row=0, column=0)  # define left margin in column 0
        sbb = tk.Scrollbar(self.my_box)
        sbb.grid(row=1, column=2, sticky=tk.N + tk.S)
        self.mylist = tk.Listbox(self.my_box, yscrollcommand=sbb.set, font=self.font, height=16, width=40, bd=3)
        self.mylist.grid(row=1, column=1, sticky=tk.N + tk.S + tk.E + tk.W)
        sbb.config(command=self.mylist.yview)
        for idx, elem in enumerate(self.alt_range):
            self.mylist.insert(idx, elem)
        self.button = ttk.Button(self.my_box, style='MyButton.TButton', text=kwargs.pop('button_text', "o.k."),
                                 takefocus=False, command=self.button_pressed)
        self.button.grid(row=2, column=0, columnspan=4, padx=20, pady=20)

    def button_pressed(self):
        try:
            selected_elem = self.alt_range[self.mylist.curselection()[0]]
            self.action(self.my_box, selected_elem)
            self.my_box.destroy()
        except IndexError:
            MyMsgBox(self.my_box, "Please select one list element.", title="Error", block=True)
