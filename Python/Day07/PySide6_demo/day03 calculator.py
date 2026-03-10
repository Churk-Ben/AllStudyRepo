from PySide6.QtWidgets import QApplication, QWidget
from ui.Ui_calculator import Ui_Form


class MainWindow(QWidget, Ui_Form):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.result = ""
        self.bind()

    def bind(self):
        self.pushButton_0.clicked.connect(lambda: self.add("0"))
        self.pushButton_1.clicked.connect(lambda: self.add("1"))
        self.pushButton_2.clicked.connect(lambda: self.add("2"))
        self.pushButton_3.clicked.connect(lambda: self.add("3"))
        self.pushButton_4.clicked.connect(lambda: self.add("4"))
        self.pushButton_5.clicked.connect(lambda: self.add("5"))
        self.pushButton_6.clicked.connect(lambda: self.add("6"))
        self.pushButton_7.clicked.connect(lambda: self.add("7"))
        self.pushButton_8.clicked.connect(lambda: self.add("8"))
        self.pushButton_9.clicked.connect(lambda: self.add("9"))
        self.pushButton_add.clicked.connect(lambda: self.add("+"))
        self.pushButton_sub.clicked.connect(lambda: self.add("-"))
        self.pushButton_mul.clicked.connect(lambda: self.add("*"))
        self.pushButton_div.clicked.connect(lambda: self.add("/"))
        self.pushButton_dot.clicked.connect(lambda: self.add("."))
        self.pushButton_enter.clicked.connect(lambda: self.output())
        self.pushButton_back.clicked.connect(lambda: self.back())
        self.pushButton_clear.clicked.connect(lambda: self.clear())

    def add(self, num):
        self.lineEdit.setText(self.lineEdit.text() + num)
        self.result += num
    
    def back(self):
        self.result = self.result[:-1]
        self.lineEdit.setText(self.result)

    def clear(self):
        self.lineEdit.setText("")
        self.result = ""

    def output(self):
        try:
            result = str(eval(self.result))
            self.lineEdit.setText(result)
            self.result = ""
        except:
            self.lineEdit.setText("Error")
            self.result = ""

if __name__ == "__main__":
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec()
