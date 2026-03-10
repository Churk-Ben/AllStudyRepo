from PySide6.QtWidgets import QApplication, QWidget
from ui.Ui_convertor import Ui_Form

class MainWindow(QWidget, Ui_Form):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.lengthUnit=["千米","米","分米","厘米"]
        self.weightUnit=["克","千克","斤"]

        

if __name__ == "__main__":
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec()