from threading import Thread


class MyThread(Thread):
    def __init__(self, func):
        Thread.__init__(self)
        self.__func = func
        self.stop = False

    def run(self):
        while not self.stop:
            self.__func()
