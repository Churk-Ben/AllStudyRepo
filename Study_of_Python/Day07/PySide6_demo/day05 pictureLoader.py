from PySide6.QtWidgets import (
    QApplication,
    QWidget,
    QLabel,
    QVBoxLayout,
    QFileDialog,
    QSlider,
    QPushButton
)
from PySide6.QtCore import Qt
from PIL import Image, ImageQt, ImageFilter


class PictureLoader(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Picture Loader")
        self.btn=QPushButton("打开图像")
        self.btn.clicked.connect(self.openImage)
        self.lbShowImage = QLabel()

        self.slider = QSlider(Qt.Orientation.Horizontal)
        self.slider.setRange(0, 20)

        self.mainLayout = QVBoxLayout()
        self.mainLayout.addWidget(self.btn)
        self.mainLayout.addWidget(self.lbShowImage)
        self.mainLayout.addWidget(self.slider)
        self.setLayout(self.mainLayout)

        self.slider.valueChanged.connect(self.changeImage)

    def openImage(self):
        self.img=Image.open(QFileDialog.getOpenFileName(self,'选择图像','./res/','图像文件(*.jpg *.png *.gif)')[0])
        pixmap=ImageQt.toqpixmap(self.img.filter(ImageFilter.GaussianBlur(self.slider.value())))
        self.pixmap=pixmap.scaled(self.lbShowImage.width(),self.lbShowImage.height(),Qt.AspectRatioMode.KeepAspectRatio)
        self.lbShowImage.setPixmap(self.pixmap)

    def changeImage(self):
        pixmap=ImageQt.toqpixmap(self.img.filter(ImageFilter.GaussianBlur(self.slider.value())))
        self.pixmap=pixmap.scaled(self.lbShowImage.width(),self.lbShowImage.height(),Qt.AspectRatioMode.KeepAspectRatio)
        self.lbShowImage.setPixmap(self.pixmap)
        


if __name__ == "__main__":
    app = QApplication([])
    window = PictureLoader()
    window.show()
    app.exec()
