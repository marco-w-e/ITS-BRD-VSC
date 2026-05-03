"""
   Widget to read input number
"""

import tkinter as tk
import tkinter.ttk as ttk
from GUI.help_button_widget import HelpButton
from GUI.select_label_widget import SelectLabel


class InputScale(ttk.Frame):
    """ Read input value via text entry and scale widget"""
    def __init__(self, master, **kwargs):
        self.length = kwargs.pop('width', 100)
        ttk.Frame.__init__(self, style='MyFrame.TFrame')
        self.help_text = kwargs.pop('help_text', " ")
        self.label = kwargs.pop('label', " ")
        self.valid_input_label = kwargs.pop('valid_input_label', " ")
        self.invalid_input_label = kwargs.pop('invalid_input_label', " ")
        self.min_value, self.max_value = kwargs.pop('min_value', 0), kwargs.pop('max_value', 100)  # min & may of range
        self.com_var = kwargs.pop('com_var', None)
        self.valid_neighbor = kwargs.pop('valid_neighbor', lambda x: x)
        self.com_var.trace('w', lambda a, b, c: self.set_status_label())
        self.textual_entry, self.status_label, self.help_button, self.scale = None, None, None, None
        self.generate_widgets(master)

    def set_disabled(self, flag):
        for widget in [self, self.label, self.scale, self.status_label]:
            widget.state(['disabled' if flag else '!disabled'])
        self.textual_entry.configure(state='disabled' if flag else 'normal')

    def generate_widgets(self, master):
        # Label
        self.label = ttk.Label(self, text=self.label, style='MyLabel.TLabel', width=20, anchor=tk.E)
        self.label.grid(column=0, row=0, padx=5, pady=5)
        # Textual entry
        valid_cmd = self.register(self.set_status_label)
        self.textual_entry = ttk.Entry(self, textvariable=self.com_var, style='MyEntry.TEntry',
                                       font=ttk.Style().lookup('.', 'font'))
        self.textual_entry.grid(column=1, row=0, padx=5, pady=5)
        # Status entry
        self.status_label = SelectLabel(self, width=20,
                                        label_list={'valid': {'foreground': 'black', 'text': self.valid_input_label},
                                                    'invalid': {'foreground': 'red', 'text': self.invalid_input_label}})
        self.status_label.grid(column=2, row=0, padx=5, pady=5)
        # Help button
        self.help_button = HelpButton(self, master, help_text=self.help_text)
        self.help_button.grid(column=3, row=0, padx=5, pady=5)
        # Scale area
        self.scale = ttk.Scale(self, from_=self.min_value, to=self.max_value, orient=tk.HORIZONTAL,
                               length=self.length, variable=self.com_var,
                               command=lambda x: self.set_com_var_and_status_label(self.valid_neighbor(x)),
                               style='MyScale.Horizontal.TScale')
        self.scale.grid(column=0, columnspan=4, row=1, padx=5, pady=5)

    def set_com_var_and_status_label(self, v):
        self.com_var.set(v)
        self.set_status_label()

    def set_status_label(self):
        valid = 'valid'
        try:
            self.com_var.get()
        except ValueError:
            valid = 'invalid'
        self.status_label.set_label(valid)
        return True
