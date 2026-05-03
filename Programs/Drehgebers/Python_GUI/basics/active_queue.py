"""
    This queue contains a queue and an event thread. A boolean parameter will be
    added to push method. If this parameter is true the event thread will execute
    its action. Since a separate thread executes the event, it does not block the
    put action. Furthermore several puts may execute only one event.
    This behavior is important since actions executing by the GUI might block until
    the current of the GUI has been finished.
"""
from basics import event_thread
import queue


class ActiveQueue(queue.Queue):
    def __init__(self):
        queue.Queue.__init__(self)
        self.thread = event_thread.EventThread()

    def put(self, item, block=True, timeout=None, gen_event=False):
        queue.Queue.put(self, item, block, timeout)
        if gen_event:
            self.thread.set_event()

    def clear(self):
        try:
            while True:
                self.get_nowait()
        except queue.Empty:
            pass

