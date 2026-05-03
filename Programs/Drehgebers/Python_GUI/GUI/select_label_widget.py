import tkinter.ttk as ttk


class SelectLabel(ttk.Label):
    """ A Label-widget that defines a dictionary of labels to be displayed.
        Each Label is defined by its color and text."""
    def __init__(self, master=None, **kwargs):
        # @param  label_list  List of Label that can be displayed in the label
        #         structure of the label list
        #               {'name label 1': {'foreground': 'color', 'text': 'text'}, ... }
        self.labels = kwargs.pop('label_list', dict())
        ttk.Label.__init__(self, master, style='MyLabel.TLabel', text=" ", **kwargs)

    def set_label(self, label):
        for item in self.labels[label].items():
            self.__setitem__(item[0], item[1])
