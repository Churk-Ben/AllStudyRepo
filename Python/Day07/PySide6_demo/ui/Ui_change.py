# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'change.ui'
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
from PySide6.QtWidgets import (QApplication, QPushButton, QSizePolicy, QWidget)
import res_rc

class Ui_Form(object):
    def setupUi(self, Form):
        if not Form.objectName():
            Form.setObjectName(u"Form")
        Form.resize(240, 240)
        Form.setMinimumSize(QSize(240, 240))
        Form.setMaximumSize(QSize(240, 240))
        Form.setStyleSheet(u"")
        self.pushButton = QPushButton(Form)
        self.pushButton.setObjectName(u"pushButton")
        self.pushButton.setGeometry(QRect(20, 20, 201, 201))
        self.pushButton.setStyleSheet(u"border-radius:12px;\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.121547 rgba(255, 175, 175, 255), stop:0.878453 rgba(78, 191, 228, 255));\n"
"\n"
"")
        icon = QIcon()
        icon.addFile(u":/images/21.jpg", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        icon.addFile(u":/images/22.jpg", QSize(), QIcon.Mode.Normal, QIcon.State.On)
        icon.addFile(u":/images/22.jpg", QSize(), QIcon.Mode.Selected, QIcon.State.Off)
        self.pushButton.setIcon(icon)
        self.pushButton.setIconSize(QSize(180, 180))
        self.pushButton.setCheckable(True)
        self.pushButton.setChecked(False)
        self.pushButton.setAutoRepeat(False)
        self.pushButton.setAutoExclusive(False)
        self.pushButton.setAutoDefault(True)
        self.pushButton.setFlat(False)

        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Form", None))
        self.pushButton.setText("")
    # retranslateUi

