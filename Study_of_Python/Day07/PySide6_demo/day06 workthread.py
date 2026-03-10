from PySide6.QtCore import QThread, Signal
from PySide6.QtWidgets import QApplication, QWidget

class WorkerThread(QThread):
    testsignal = Signal(str)

    def __init__(self):
        super().__init__()
        
    def run(self):
        for i in range(10):
            self.testsignal.emit(f"Test message {i}")
            self.msleep(1000)

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Worker Thread Example")
        self.resize(300, 200)
        self.worker = WorkerThread()
        self.worker.testsignal.connect(self.handle_message)
        self.worker.start()

    def handle_message(self, message):
        print(message)

if __name__ == '__main__':
    app = QApplication()
    main_window = MainWindow()
    main_window.show()
    app.exec()