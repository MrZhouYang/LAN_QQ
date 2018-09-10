#-------------------------------------------------
#
# Project created by QtCreator 2018-08-28T20:58:47
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QQ_Client
TEMPLATE = app

INCLUDEPATH += ./src/model \
            ./src/ui \
            ./src/ui/Birthday \
            ./src/Communication \
            ./src/ui/LinkButton
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    src/model/config.cpp \
    src/model/data_pools.cpp \
    src/model/singleton.cpp \
    src/ui/chatform.cpp \
    src/ui/collapseview.cpp \
    src/ui/collapseviewitem.cpp \
    src/ui/colorpickform.cpp \
    src/ui/litteriem.cpp \
    src/ui/loginform.cpp \
    src/ui/mainform.cpp \
    src/ui/moveableframelesswindow.cpp \
    src/ui/registerdialog.cpp \
    src/ui/Birthday/CalendarDialog.cpp \
    src/ui/Birthday/CustomLineEdit.cpp \
    src/ui/Birthday/CustomCalendar.cpp \
    src/ui/Birthday/CustomComboBox.cpp \
    src/Communication/QQRegisterCtrl.cpp \
    src/Communication/QQTcpSocket.cpp \
    src/Communication/IMEncryption.cpp \
    src/ui/loginsetting.cpp \
    src/Communication/QQLoginCtrl.cpp \
    src/Communication/qqdatabasectrl.cpp \
    src/Communication/QQClientFileCtrl.cpp \
    src/Communication/qqmainctrl.cpp \
    src/ui/LinkButton/qqlinkbutton.cpp \
    src/ui/LinkButton/qqlinkfriendbutton.cpp \
    src/ui/qqlatestmessagelistwidget.cpp

HEADERS  += \
    src/model/config.h \
    src/model/data_pools.h \
    src/model/singleton.h \
    src/ui/chatform.h \
    src/ui/collapseview.h \
    src/ui/collapseviewitem.h \
    src/ui/colorpickform.h \
    src/ui/litteriem.h \
    src/ui/loginform.h \
    src/ui/mainform.h \
    src/ui/moveableframelesswindow.h \
    src/ui/registerdialog.h \
    src/ui/Birthday/CalendarDialog.h \
    src/ui/Birthday/CustomLineEdit.h \
    src/ui/Birthday/CustomCalendar.h \
    src/ui/Birthday/CustomComboBox.h \
    src/Communication/qqConstant.h \
    src/Communication/QQRegisterCtrl.h \
    src/Communication/QQTcpSocket.h \
    src/Communication/IMEncryption.h \
    src/ui/loginsetting.h \
    src/Communication/QQLoginCtrl.h \
    src/Communication/qqdatabasectrl.h \
    src/Communication/QQClientFileCtrl.h \
    src/Communication/qqmainctrl.h \
    src/ui/LinkButton/qqlinkbutton.h \
    src/ui/LinkButton/qqlinkfriendbutton.h \
    src/ui/qqlatestmessagelistwidget.h

FORMS    += \
    src/ui/chatform.ui \
    src/ui/collapseviewitem.ui \
    src/ui/colorpickform.ui \
    src/ui/litteriem.ui \
    src/ui/loginform.ui \
    src/ui/mainform.ui \
    src/ui/registerdialog.ui \
    src/ui/loginsetting.ui

RESOURCES += \
    rs/rs.qrc
