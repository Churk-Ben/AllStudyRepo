from PySide6.QtWidgets import QApplication, QWidget, QTextEdit, QVBoxLayout, QPushButton

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setupUI()
        self.cnt=0
    
    def setupUI(self):
        self.setWindowTitle("Append Text")
        self.setFixedSize(240, 360)
        
        self.textEdit = QTextEdit()
        self.textEdit.setPlaceholderText("waiting...")
        self.textEdit.setReadOnly(True)
        
        self.appendButton = QPushButton("Append")
        self.appendButton.clicked.connect(self.appendText)
        
        layout = QVBoxLayout()
        layout.addWidget(self.textEdit)
        layout.addWidget(self.appendButton)
        self.setLayout(layout)

    def appendText(self):
        self.cnt+=1
        self.textEdit.append(f"This is line {self.cnt}")

if __name__ == "__main__":
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec()