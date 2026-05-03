from pi.pi_pico import PiPico
from pi.pi_answer import AnswerType
from GUI.my_msg_box_widget import MyMsgBox
from my_exceptions import ProtocolErr
from serial.serialutil import SerialException
import queue


class PiProtocol(PiPico):
    def __init__(self):
        PiPico.__init__(self)
        self.running = None    # tk variable running
        self.angle = None      # tk variable angle
        self.velocity = None   # tk variable angular  velocity
        self.__angle_of_Pi = None  # Angle stored in pi
        self.__velocity_of_Pi = None  # Angular velocity stored in pi

    def connect(self, parent_widget, dev):
        try:
            PiPico.open(self, dev)
            # Start communication with Pi Pico
            self.__angle_of_Pi, self.__velocity_of_Pi = self.__send_cmd_multiple(" ", None)
            # pi sets angle and angular acceleration only during connection phase.
            if self.__angle_of_Pi is not None and self.__velocity_of_Pi is not None:
                self.angle.set(str(self.__angle_of_Pi))
                self.velocity.set(str(self.__velocity_of_Pi))
                self.running.set(False)  # square generators does not run - even if GUI assumes that it is running
        except ProtocolErr as e:
            self.__report_err(e.value + "\nDid you select the serial port connected to Pi Pico?", parent_widget, True)
        except SerialException as e:
            self.__report_err("Failed to open serial connection.\n" + str(e), parent_widget, True)
        if self.__angle_of_Pi is None or self.__velocity_of_Pi is None:
            self.__report_err("Selected COM Port does not belong to Pi Pico.", parent_widget, True)

    def __send_cmd_multiple(self, cmd, cmd_answer, retries=2, stop_after_answer=False):
        while retries > 0:
            try:
                retries = retries - 1
                self.answer_queue.clear()
                self.write(cmd)
                return self.answer_queue.get_ans(cmd_answer, stop_after_answer)
            except queue.Empty:
                if retries == 0:
                    raise ProtocolErr("Protocol error: Time out.")

    def set_angle(self):
        #  angle stores valid values
        angle = float(self.angle.get())
        if angle != self.__angle_of_Pi:
            try:
                self.__angle_of_Pi, self.__velocity_of_Pi = \
                    self.__send_cmd_multiple("a" + self.angle.get()+"\n", AnswerType.AskForAngle)
            except ProtocolErr as e:
                raise ProtocolErr("Set angle to Pi Pico: " + e.value, True)
            except ValueError:
                raise ProtocolErr("Internal error while setting angle to Pi Pico: Valid angle required.", False)
            if self.__angle_of_Pi is None:
                raise ProtocolErr("Protocol error: Angle missing.", True)
            if self.__velocity_of_Pi is None:
                raise ProtocolErr("Protocol error: Angular velocity missing.", True)
            if angle != self.__angle_of_Pi:
                raise ProtocolErr("Internal error: Could not set angle in Pi Pico. Reboot Pi Pico.", True)

    def set_velocity(self):
        #  angular velocity stores valid values
        velocity = float(self.velocity.get())
        if velocity != self.__velocity_of_Pi:
            try:
                self.__angle_of_Pi, self.__velocity_of_Pi = \
                    self.__send_cmd_multiple("s" + self.velocity.get()+"\n", AnswerType.AskForVelocity)
            except ProtocolErr as e:
                raise ProtocolErr("Set angular velocity to Pi Pico: " + e.value, True)
            except ValueError:
                raise ProtocolErr("Internal error: Could not set angular velocity in Pi Pico. Reboot Pi Pico.", True)
            if self.__angle_of_Pi is None:
                raise ProtocolErr("Protocol error: Angle missing.", True)
            if self.__velocity_of_Pi is None:
                raise ProtocolErr("Protocol error: Angular velocity missing.", True)
            if velocity != self.__velocity_of_Pi:
                raise ProtocolErr("Internal error: Could not set angular velocity in Pi Pico. Reboot Pi Pico.", True)

    def start(self, parent_widget):
        try:
            if not self.is_connected():
                self.running.set(False)
                raise ProtocolErr("No connection to Pi Pico.", False)
            if self.running.get():
                raise ProtocolErr("Square wave generator runs.", False)
            self.set_angle()
            self.set_velocity()
            self.__send_cmd_multiple("r", AnswerType.WaitForStop, 2, True)
            self.running.set(True)
        except ProtocolErr as e:
            self.__report_err(e.value, parent_widget, e.close_connection)

    def stop(self, parent_widget):
        """ If Stop will be pressed in the moment when square wave generation
            finished, no GenerationStopped answer will be generated.
            In this case the current angle and speed will be reported.
            Hence do not wait for GenerationStopped answer.
        """
        try:
            if not self.is_connected():
                self.running.set(False)
                raise ProtocolErr("No connection to Pi Pico.", False)
            if not self.running.get():
                raise ProtocolErr("Square wave generator does not run.", False)
            if(self.__angle_of_Pi, self.__velocity_of_Pi) != \
                    self.__send_cmd_multiple("x", None):
                raise ProtocolErr("Protocol with Pi Pico failed. Connection closed.", True)
            self.running.set(False)
        except ProtocolErr as e:
            self.__report_err(e.value, parent_widget, e.close_connection)

    def __report_err(self, txt, widget, close):
        if close:
            txt = txt + "\nConnection to Pi Pico closed.\nReboot Pi Pico."
            self.close()
        MyMsgBox(widget, txt, title="Error", block=True)
