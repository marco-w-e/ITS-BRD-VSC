import tkinter as tk
import tkinter.ttk as ttk
from tkinter.scrolledtext import ScrolledText
from GUI.traffic_light_widget import TrafficLight
from GUI.input_scale_widget import InputScale
from GUI.select_label_widget import SelectLabel
from GUI.selection_box_widget import SelectBox
from basics.my_string_var import MyStringVar
from GUI.my_msg_box_widget import MyMsgBox
import math

help_text_angle = "Requirements concerning an angle value:\n\
   - Range of values: -210000000.0° ... 210000000.0°.\n\
   - A maximum of one digit after the decimal point is allowed.\n\
   - The angle must be divisible by 0.3.\n\n\
Angle cannot be changed while square wave generator\n\
is running."

min_angle = -210000000.0
max_angle = 210000000.0


def is_valid_angle(angle_str):
    angle = float(angle_str)
    if not ((angle * 10).is_integer() and abs(angle * 10) % 3 == 0 and angle != 0 and min_angle <= angle <= max_angle):
        raise ValueError
    return angle_str


def nearest_valid_angle(angle):
    angle = float(angle)
    angle = angle if angle != 0 else 0.1
    v = math.floor(angle * 10)
    left, right = v, v
    while right % 3 != 0:
        right = right + 1
    right = min(right, max_angle * 10)
    while left % 3 != 0:
        left = left - 1
    left = max(left, min_angle * 10)
    left = left if left != 0 else right
    right = right if right != 0 else left
    neighbor = right if abs(abs(left) - abs(v)) < abs(abs(right) - abs(v)) else left
    return float(neighbor) / 10


help_text_velocity = "Requirements concerning an angular velocity value:\n\
   - Range of values: 1°/s ... 37500°/s.\n\
   - Angular speed must be an integer.\n\
   - Angular speed must be a divisor of 37500000.\n\n\
Angular velocity cannot be changed while\n\
square wave generator is running."

min_velocity = 1
max_velocity = 37500


def is_valid_velocity(velocity_str):
    velocity = float(velocity_str)
    if not(math.floor(velocity) == velocity and
           min_velocity <= velocity <= max_velocity and (37500000 % velocity == 0)):
        raise ValueError
    return velocity_str


def nearest_valid_velocity(angular_velocity):
    angular_velocity = float(angular_velocity)
    v = math.floor(angular_velocity)
    left, right = v, v
    while 37500000 % right != 0:
        right = right + 1
    right = min(right, max_velocity)
    while 37500000 % left != 0:
        left = left - 1
    left = max(left, min_velocity)
    return right if abs(abs(left) - abs(v)) < abs(abs(right) - abs(v)) else left


class GUI(tk.Tk):
    def __init__(self, pi):
        tk.Tk.__init__(self)
        self.height = 450
        self.width = 800
        self.title("Square Wave Generator")
        self.configure(background='white')
        self.font = 'Arial 13'
        self.pi = pi
        self.angle, self.velocity, self.connect_button, self.start_button = None, None, None, None
        self.stop_button, self.traffic_light, self.info_label, self.text_area = None, None, None, None
        self.running = tk.BooleanVar(value=False)  # wave generator is running
        self.angle_var = MyStringVar(is_valid_angle, "")
        self.velocity_var = MyStringVar(is_valid_velocity, "")
        # References to common TK variables
        self.pi.running, self.pi.angle, self.pi.velocity = self.running, self.angle_var, self.velocity_var
        self.style = ttk.Style()
        self.define_styles()
        self.start_widgets()
        self.running.trace('w', lambda a, b, c: self.update_running())
        self.bind("<<UpdateLog>>", lambda x: self.print_queue(self.pi.text_queue))
        self.bind("<<GenerationStopped>>", lambda x:  self.running.set(False))
        self.pi.text_queue.thread.action = lambda: self.event_generate("<<UpdateLog>>")
        self.pi.answer_queue.thread.action = lambda: self.event_generate("<<GenerationStopped>>")

    def start(self):
        self.mainloop()

    def start_widgets(self):
        # Input angle
        self.angle = InputScale(self, width=self.width, height=self.height, label="angle [°] :",
                                valid_input_label="valid angle", invalid_input_label="invalid angle",
                                com_var=self.angle_var,
                                valid_neighbor=nearest_valid_angle,
                                min_value=min_angle, max_value=max_angle,
                                help_text=help_text_angle)
        self.angle.grid(row=0, column=0, columnspan=5, padx=20, pady=20)
        self.pi.set_angle_in_GUI = self.angle.set_com_var_and_status_label
        # Input angular velocity
        self.velocity = InputScale(self, width=self.width, label="angular velocity [°/s] :",
                                   valid_input_label="valid angular velocity",
                                   invalid_input_label="invalid angular velocity",
                                   com_var=self.velocity_var,
                                   valid_neighbor=nearest_valid_velocity,
                                   min_value=min_velocity, max_value=max_velocity,
                                   help_text=help_text_velocity)
        self.velocity.grid(row=1, column=0, columnspan=5, padx=20, pady=10)
        self.pi.set_velocity_in_GUI = self.velocity.set_com_var_and_status_label
        self.connect_button = ttk.Button(self, text="Connect", style='FixButton.MyButton.TButton',
                                         command=lambda: self.callback_connect_button(), takefocus=False)
        self.connect_button.grid(row=2, column=0, padx=20, pady=10, sticky=tk.W)
        self.start_button = ttk.Button(self, text="Start", style='FixButton.MyButton.TButton',
                                       command=lambda: self.pi.start(self), takefocus=False)
        self.start_button.grid(row=2, column=1, padx=0, pady=10)
        self.stop_button = ttk.Button(self, text="Stop", style='FixButton.MyButton.TButton',
                                      command=lambda: self.pi.stop(self), takefocus=False)
        self.stop_button.grid(row=2, column=2, padx=20, pady=10, sticky=tk.E)
        self.traffic_light = TrafficLight(self)
        self.traffic_light.grid(row=2, column=3, padx=0, pady=10)
        self.info_label = SelectLabel(self, width=41, background="white",
                                      label_list={'running': {'foreground': 'red', 'text': "running"},
                                                  'ready': {'foreground': 'green', 'text': "ready"}})
        self.info_label.grid(row=2, column=4, padx=20, pady=10, sticky=tk.E)
        self.text_area = ScrolledText(self, width=87, height=12, state='disabled',
                                      fg='black', bg="white", font=self.font)
        self.text_area.focus()
        self.text_area.grid(row=3, column=0, columnspan=5, padx=20, pady=20, sticky=tk.W)

    def print_queue(self, queue):
        while not queue.empty():
            self.print_text(queue.get())

    def print_text(self, text):
        self.text_area.configure(state='normal')
        self.text_area.insert(tk.INSERT, text)
        self.text_area.configure(state='disabled')
        self.text_area.yview(tk.END)

    def callback_connect_button(self):
        if self.pi.is_connected():
            MyMsgBox(self, "Connection to Pi Pico already exists.", title="Error", block=True)
            return
        help_text = "List of COM ports connected via USB.\n" + \
                    "If this list is empty, then Pi Pico is \nnot connected to your computer."
        SelectBox(self, title="Select USB COM port for communication with Pi Pico",
                  button_text="connect", alt_range=self.pi.get_serial_USB_interfaces(),
                  help_text=help_text, action=self.pi.connect)

    def define_styles(self):
        bg_clr_enabled = 'grey80'
        bg_clr_disabled = 'grey95'
        print("theme list: " + str(self.style.theme_names()))
        self.style.theme_use('default')
        print("current theme: " + self.style.theme_use())
        self.style.configure('.', font=self.font)
        self.style.configure('MyButton.TButton', foreground='black')
        self.style.configure('FixButton.MyButton.TButton', width=10, foreground='black')
        self.style.configure('OneCharButton.MyButton.TButton', font=self.font + " bold", width=1)
        self.style.configure('MyLabel.TLabel', foreground='black', background=bg_clr_enabled)
        self.style.configure('MsgBox.TLabel', foreground='black', background='white')
        self.style.configure('MyFrame.TFrame', background=bg_clr_enabled)
        self.style.configure('MyEntry.TEntry', foreground='black', fieldbackground=bg_clr_enabled)
        self.style.configure('MyScale.Horizontal.TScale', background=bg_clr_enabled)
        self.style.configure('MyScale.Horizontal.TScale', troughcolor=bg_clr_enabled)
        self.style.map('MyFrame.TFrame', background=[('disabled', bg_clr_disabled), ('!disabled', bg_clr_enabled)])
        self.style.map('MyLabel.TLabel', background=[('disabled', bg_clr_disabled), ('!disabled', bg_clr_enabled)])
        self.style.map('MyEntry.TEntry', fieldbackground=[('disabled', bg_clr_disabled), ('!disabled', bg_clr_enabled)])
        self.style.map('MyScale.Horizontal.TScale',
                       background=[('disabled', bg_clr_disabled), ('!disabled', bg_clr_enabled)],
                       troughcolor=[('disabled', bg_clr_disabled), ('!disabled', bg_clr_enabled)])

    def update_running(self):
        v = self.running.get()
        self.traffic_light.set('red' if v else 'green')
        self.info_label.set_label('running' if v else 'ready')
        self.angle.set_disabled(v)
        self.velocity.set_disabled(v)
