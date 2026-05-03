#
# Simpler wrapper for serial interface to pi
#
from serial import Serial, EIGHTBITS, PARITY_NONE, STOPBITS_ONE
from serial.tools import list_ports


class SerialWrapper(Serial):
    def __init__(self, **kwargs):
        Serial.__init__(self)
        self.baudrate = kwargs.pop('baudrate', 115200)
        self.bytesize = kwargs.pop('bytesize', EIGHTBITS)
        self.parity = kwargs.pop('parity', PARITY_NONE)
        self.stopbits = kwargs.pop('stopbits', STOPBITS_ONE)

    def readline(self):
        return SerialWrapper.__clean_str(bytearray(Serial.readline(self))).decode()

    def __is_configured(self):
        try:
            self.inWaiting()
            return True
        except:
            return False

    def is_connected(self):
        if not self.__is_configured() and self.is_open:
            self.close()
        return self.is_open

    def open(self, dev):
        self.port = dev
        Serial.open(self)
        self.flushInput()
        self.flushOutput()

    @staticmethod
    def get_serial_USB_interfaces():
        return [elem.device for elem in list_ports.comports() if elem.vid is not None and elem.pid is not None]

    @staticmethod
    def __clean_str(val):
        # delete terminal control sequences and "\r"
        i = 0
        while i < len(val):
            if val[i] == ord('\r') and (i + 1) < len(val) and val[i + 1] == ord('\n'):
                val.pop(i)
            elif val[i] == 0x1b and (i + 1) < len(val) and val[i + 1] in {ord('c')}:
                val.pop(i)
                val.pop(i)
            elif val[i] == 0x1b and (i + 1) < len(val) and not (val[i + 1] in {ord('c')}):
                raise Exception("unexpected terminal control sequence")
            else:
                i = i + 1
        return val

    def write(self, txt):
        Serial.write(self, (txt.replace("\n", "\r\n")).encode())
