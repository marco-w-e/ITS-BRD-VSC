"""
   This active queue handles pi answers
"""
import queue

from basics.active_queue import ActiveQueue
from my_exceptions import ProtocolErr
from pi.pi_answer import AnswerType


class PiAnswerQueue(ActiveQueue):
    def __init__(self):
        self.timeout = 2
        ActiveQueue.__init__(self)

    def __check(self, a):
        if a.answer_type == AnswerType.Unknown:
            raise ProtocolErr("Got unknown answer from Pi Pico. Reboot Pi Pico.", close_connection=True)
        if a.answer_type == AnswerType.InternalError:
            raise ProtocolErr("Internal error in Pi Pico. Reboot Pi Pico.", close_connection=True)
        return a

    """ This functions reads several messages von Pi Pico. 
         It skips all messages until a message of type first occurs.
         Then it reads all following messages und updates angle an speed
         due to the contents of this messages.
         If no message of type first has occurred, the Empty Exception will be thrown.
    """
    def get_ans(self, first, stop_after_first=False):
        angle, velocity = None, None
        while first is not None:  # skip messages until message of type first occurs
            a = self.__check(self.get(True, self.timeout))
            if a.answer_type == first:
                angle, velocity = a.angle, a.velocity
                break
        try:
            while not stop_after_first:  # extract angle and velocity out of messages
                a = self.__check(self.get(angle is None or velocity is None, self.timeout))
                angle = angle if a.angle is None else a.angle
                velocity = velocity if a.velocity is None else a.velocity
        except queue.Empty:
            pass
        return angle, velocity
