# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'convertor.ui'
##
## Created by: Qt User Interface Compiler version 6.8.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QComboBox, QLabel, QLineEdit,
    QPushButton, QSizePolicy, QWidget)

class Ui_Form(object):
    def setupUi(self, Form):
        if not Form.objectName():
            Form.setObjectName(u"Form")
        Form.resize(240, 360)
        self.label_in = QLabel(Form)
        self.label_in.setObjectName(u"label_in")
        self.label_in.setGeometry(QRect(20, 30, 201, 31))
        font = QFont()
        font.setPointSize(10)
        font.setWeight(QFont.Medium)
        self.label_in.setFont(font)
        self.label_in.setStyleSheet(u"color:rgb(193, 193, 193)")
        self.label_in.setMargin(5)
        self.label_in.setIndent(0)
        self.label_out = QLabel(Form)
        self.label_out.setObjectName(u"label_out")
        self.label_out.setGeometry(QRect(20, 70, 201, 31))
        font1 = QFont()
        font1.setPointSize(14)
        font1.setBold(True)
        self.label_out.setFont(font1)
        self.label_out.setMargin(5)
        self.label_out.setIndent(0)
        self.comboBox_type = QComboBox(Form)
        self.comboBox_type.setObjectName(u"comboBox_type")
        self.comboBox_type.setGeometry(QRect(20, 120, 201, 31))
        self.lineEdit_in = QLineEdit(Form)
        self.lineEdit_in.setObjectName(u"lineEdit_in")
        self.lineEdit_in.setGeometry(QRect(20, 170, 113, 31))
        self.lineEdit_out = QLineEdit(Form)
        self.lineEdit_out.setObjectName(u"lineEdit_out")
        self.lineEdit_out.setGeometry(QRect(20, 220, 113, 31))
        self.comboBox_in = QComboBox(Form)
        self.comboBox_in.setObjectName(u"comboBox_in")
        self.comboBox_in.setGeometry(QRect(140, 170, 80, 31))
        self.comboBox_out = QComboBox(Form)
        self.comboBox_out.setObjectName(u"comboBox_out")
        self.comboBox_out.setGeometry(QRect(140, 220, 80, 31))
        self.pushButton = QPushButton(Form)
        self.pushButton.setObjectName(u"pushButton")
        self.pushButton.setGeometry(QRect(140, 290, 71, 31))

        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"\u8fdb\u5236\u8f6c\u6362\u5668", None))
        self.label_in.setText(QCoreApplication.translate("Form", u"1\u5343\u7c73=", None))
        self.label_out.setText(QCoreApplication.translate("Form", u"11111111\u516c\u91cc", None))
        self.pushButton.setText(QCoreApplication.translate("Form", u"\u8f6c\u6362", None))
    # retranslateUi

