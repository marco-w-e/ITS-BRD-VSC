"""
   Interface to Pi Pico

   Synchronisation of the variables that store the angle and the angular velocity
   in the GUI and the pi interface.
   - During connection phase the pi interface sends the values of its variables
     to the GUI.
   - During the rest of the time the GUI sends the values of its variables to
     pi interface.
"""

from pi.serial_wrapper import *
from serial import SerialException
from pi.pi_answer import PiAnswer, AnswerType
from pi.pi_answer_queue import PiAnswerQueue
from basics.my_thread import MyThread
from basics.active_queue import ActiveQueue
import sys


class PiPico(SerialWrapper):
    def __init__(self):
        SerialWrapper.__init__(self)
        self.text_queue, self.answer_queue = ActiveQueue(), PiAnswerQueue()
        self.read_thread = None

    def close(self):
        # if self.read_thread is not None:
        #     self.read_thread.stop = True
        SerialWrapper.close(self)
        if self.read_thread is not None:
            self.read_thread.join()
        self.read_thread = None

    def open(self, dev):
        self.answer_queue.clear()
        self.text_queue.clear()
        SerialWrapper.open(self, dev)
        self.read_thread = MyThread(self.__handle_input)
        self.read_thread.start()

    def __handle_input(self):
        try:
            line = self.readline()
        except (SerialException, AttributeError) as e:
            # self.read_thread.stop = True
            # return #
            sys.exit()  #  does not work on windows
        self.text_queue.put(line, gen_event=True)
        answer = PiAnswer(line)
        if answer.answer_type == AnswerType.Unknown:
            err_txt = "Unknown answer from Pi Pico. Reboot Pi Pico."
            self.text_queue.put(err_txt, gen_event=True)
        if answer.answer_type == AnswerType.InternalError:
            err_txt = "Internal error in Pi Pico. Reboot Pi Pico."
            self.text_queue.put(err_txt, gen_event=True)
        if answer.answer_type != AnswerType.WhiteSpace:
            self.answer_queue.put(answer, gen_event=(answer.answer_type == AnswerType.GenerationFinished))

    def write(self, txt):
        SerialWrapper.write(self, txt)
        self.text_queue.put(txt, gen_event=True)
