from PySide6.QtWidgets import QApplication, QWidget
from ui.Ui_login import Ui_Form

class MainWindow(QWidget, Ui_Form):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.pushButton.clicked.connect(self.login)

    def login(self):
        account = self.lineEdit_account.text()
        password = self.lineEdit_password.text()
        if account == "111" and password == "111":
            print("login success")
        else:
            print("login failed")


if __name__ == "__main__":
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec()