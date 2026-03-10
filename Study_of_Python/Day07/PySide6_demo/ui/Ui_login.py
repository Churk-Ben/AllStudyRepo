# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'login.ui'
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
from PySide6.QtWidgets import (QApplication, QLabel, QLineEdit, QPushButton,
    QSizePolicy, QWidget)

class Ui_Form(object):
    def setupUi(self, Form):
        if not Form.objectName():
            Form.setObjectName(u"Form")
        Form.resize(240, 240)
        self.label_1 = QLabel(Form)
        self.label_1.setObjectName(u"label_1")
        self.label_1.setGeometry(QRect(30, 30, 61, 21))
        font = QFont()
        font.setPointSize(10)
        self.label_1.setFont(font)
        self.label_1.setAlignment(Qt.AlignmentFlag.AlignLeading|Qt.AlignmentFlag.AlignLeft|Qt.AlignmentFlag.AlignTop)
        self.label_2 = QLabel(Form)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setGeometry(QRect(30, 100, 61, 21))
        self.label_2.setFont(font)
        self.label_2.setAlignment(Qt.AlignmentFlag.AlignLeading|Qt.AlignmentFlag.AlignLeft|Qt.AlignmentFlag.AlignTop)
        self.pushButton = QPushButton(Form)
        self.pushButton.setObjectName(u"pushButton")
        self.pushButton.setGeometry(QRect(130, 180, 75, 31))
        self.lineEdit_account = QLineEdit(Form)
        self.lineEdit_account.setObjectName(u"lineEdit_account")
        self.lineEdit_account.setGeometry(QRect(30, 50, 181, 31))
        self.lineEdit_password = QLineEdit(Form)
        self.lineEdit_password.setObjectName(u"lineEdit_password")
        self.lineEdit_password.setGeometry(QRect(30, 120, 181, 31))

        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"\u767b\u5f55\u6846", None))
        self.label_1.setText(QCoreApplication.translate("Form", u"\u8d26\u53f7", None))
        self.label_2.setText(QCoreApplication.translate("Form", u"\u5bc6\u7801", None))
        self.pushButton.setText(QCoreApplication.translate("Form", u"\u767b\u5f55", None))
        self.lineEdit_account.setPlaceholderText(QCoreApplication.translate("Form", u"Account", None))
        self.lineEdit_password.setPlaceholderText(QCoreApplication.translate("Form", u"Password", None))
    # retranslateUi

