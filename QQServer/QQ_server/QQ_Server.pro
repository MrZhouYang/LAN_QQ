#-------------------------------------------------
#
# Project created by QtCreator 2018-08-28T20:51:30
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QQ_Server
TEMPLATE = app
INCLUDEPATH += ./UI \
             ./Datebase \
             ./Communication \
             ./Encryption

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
    Communication/qqservermessagectrl.cpp \
    UI/qqserverwindow.cpp \
    Database/qqdatabasectrl.cpp \
    Communication/qqtcpserver.cpp \
    Communication/qquser.cpp \
    Communication/qqclientsocketctrl.cpp

HEADERS  += \
    Communication/qqservermessagectrl.h \
    UI/qqserverwindow.h \
    Database/qqdatabasectrl.h \
    Communication/qqtcpserver.h \
    Communication/qquser.h \
    Communication/qqclientsocketctrl.h \
    Communication/qqConstant.h \
    Encryption/IMEncryption.h

FORMS    += \
    UI/qqserverwindow.ui
