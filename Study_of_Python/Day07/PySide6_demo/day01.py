from PySide6.QtWidgets import QApplication, QWidget,QPushButton

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("My App")
        self.setGeometry(500,200,200,200)

        btn=QPushButton("Click me",self)
        btn.setGeometry(50,50,100,50)
        btn.clicked.connect(self.hello)

    def hello(self):
        print("Hello World")

if __name__ == "__main__":
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec()