#-------------------------------------------------
#
# Project created by QtCreator 2021-05-16T09:23:32
#
#-------------------------------------------------

QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VLinkTester
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    Components/CompPack.cpp \
    Management/Mng_System.cpp \
    dlgUDP.cpp \
    dlgSerial.cpp \
    VLinkTester.cpp \
    Management/Mng_Settings.cpp

HEADERS += \
    Components/CompPack.h \
    Defines.h \
    Management/Mng_System.h \
    dlgUDP.h \
    dlgSerial.h \
    VLinkTester.h \
    Management/Mng_Settings.h

FORMS += \
    Components/CompPack.ui \
    dlgUDP.ui \
    dlgSerial.ui \
    VLinkTester.ui

include(E:\Projects\Git\VLink\VLink.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
