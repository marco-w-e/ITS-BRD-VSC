class ProtocolErr(Exception):
    def __init__(self, value="", close_connection=True):
        self.value = value
        self.close_connection = close_connection

    def __str__(self):
        return "ProtocolErr" + str(self.value)
