"""
   Data from Pi Pico
"""

from enum import Enum, unique
import re


@unique
class AnswerType(Enum):
    Unknown = 0
    WhiteSpace = 1
    AngleOfPi = 2
    VelocityOfPi = 3
    AskForAngle = 4
    AskForVelocity = 5
    WaitForStop = 6
    WaitForAnyKey = 7
    WrongAngle = 8
    WrongVelocity = 9
    GenerationStopped = 10
    PressAnyKeyToContinue = 11
    InternalError = 12
    GenerationFinished = 13


class PiAnswer:
    def __init__(self, s):
        self.answer_type, self.angle, self.velocity = AnswerType.Unknown, None, None
        static_map = {"\n": AnswerType.WhiteSpace,
                      "Press any key to start.\n": AnswerType.WhiteSpace,
                      "Press a       to enter a": AnswerType.WhiteSpace,
                      "Press s       to enter a": AnswerType.WhiteSpace,
                      "Press h       for help\n": AnswerType.WhiteSpace,
                      "ticks = ": AnswerType.WhiteSpace,
                      "clk_sys = ": AnswerType.WhiteSpace,
                      "Press r       to start square wave generation\n": AnswerType.WhiteSpace,
                      "Start in ": AnswerType.WhiteSpace,
                      "Version : ": AnswerType.WhiteSpace,
                      "Requirements for the value of the angle\n": AnswerType.WhiteSpace,
                      "   - Range of values: ": AnswerType.WhiteSpace,
                      "   - A maximum of one digit after the decimal point is allowed.\n": AnswerType.WhiteSpace,
                      "Requirements for the value of the angle speed\n": AnswerType.WhiteSpace,
                      "   - Angular speed must be an integer.\n": AnswerType.WhiteSpace,
                      "   - Angular speed must be a factor of ": AnswerType.WhiteSpace,
                      "Loaded program at ": AnswerType.WhiteSpace,
                      "state = ": AnswerType.WhiteSpace,
                      "Please enter an angle followed by newline:\n": AnswerType.AskForAngle,
                      "Please enter an angular speed followed by newline:\n": AnswerType.AskForVelocity,
                      "Press any key to stop square wave generator.\n": AnswerType.WaitForStop,
                      "Angle out of range.\n": AnswerType.WrongAngle,
                      "   - The angle must be divisible by 0.3.\n": AnswerType.WrongAngle,
                      "Angle speed must be an integer.\n": AnswerType.WrongVelocity,
                      "Invalid angular speed.\n": AnswerType.WrongVelocity,
                      "Angular speed has been adapted to ": AnswerType.WrongVelocity,
                      "Square wave generator stopped.\n": AnswerType.GenerationStopped,
                      "Press any key to continue.\n": AnswerType.PressAnyKeyToContinue}
        for elem, ty in static_map.items():
            if s.startswith(elem):
                self.answer_type = ty
                return
        if s.find("is not divisible by 0.3") != -1:
            self.answer_type = AnswerType.WrongAngle
        elif s.find(" : Internal error: ") != -1:
            self.answer_type = AnswerType.InternalError
        elif s.startswith("Angular Speed = ") and s.find(" degree/second\n") != -1:
            # "Angular Speed = %d degree/second\n"
            self.answer_type = AnswerType.VelocityOfPi
            matches = re.findall("[+-]?\d+", s)
            self.velocity = int(matches[0])
        elif s.startswith("Angle         = ") and s.find(" degree\n") != -1:
            # "Angle         =  %d.%d degree\n"
            self.answer_type = AnswerType.AngleOfPi
            matches = re.findall("[+-]?\d+\.\d+", s)
            self.angle = float(matches[0])
        elif s.startswith("An angle of ") and s.find(" degree was generated at ") != -1:
            # "\nAn angle of %d.%d degree was generated at an angular speed of %d degree/second.\n"
            self.answer_type = AnswerType.GenerationFinished
            matches = re.findall(r"[+-]? *(?:\d+(?:\.\d*)?|\.\d+)", s)
            self.angle = float(matches[0])
            self.velocity = int(matches[1])
