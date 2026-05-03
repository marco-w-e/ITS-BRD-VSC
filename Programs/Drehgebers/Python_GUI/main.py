from gui import GUI
from pi.pi_protocol import PiProtocol

if __name__ == '__main__':
    pi = PiProtocol()
    gui = GUI(pi)
    gui.start()
    # Clean Up
    pi.close()
    pi.answer_queue.thread.join()
    pi.text_queue.thread.join()
    print("done")
