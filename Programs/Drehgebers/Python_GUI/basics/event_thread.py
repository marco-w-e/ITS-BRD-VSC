"""
    This thread is a simpled version of a worker thread. Instead of a work queue that stores different
    tasks, this thread can execute only task defined by its function parameter action.
    The thread of this class waits for an event. Wenn this event is set, the threads
        - resets the event
        - executes its run function
        - waits for the next event
"""
import threading


class EventThread(threading.Thread):
    def __init__(self):
        self.__run = True
        self.__event = threading.Event()
        self.action = lambda: print("No action defined for this event thread.")
        threading.Thread.__init__(self)
        self.start()

    def run(self):
        while self.__run:
            self.__event.wait()
            self.__event.clear()
            if self.__run:  # Action should not be executed when thread should terminate
                try:
                    self.action()
                except RuntimeError:
                    self.__run = False

    def join(self, timeout=None):
        # cannot be called in __del__, since dell will not be called before threads is  terminated
        self.__run = False
        self.set_event()
        threading.Thread.join(self, timeout)

    def set_event(self):
        self.__event.set()
