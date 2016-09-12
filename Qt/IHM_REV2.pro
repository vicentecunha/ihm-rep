#-------------------------------------------------
#
# Project created by QtCreator 2016-06-09T17:10:42
#
#-------------------------------------------------

include(qextserialport/src/qextserialport.pri)

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHM_REV2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    protocol.cpp \
    stage.cpp \
    protocolwindow.cpp \
    database.cpp \
    savefileparser.cpp \
    rs232.c

HEADERS  += mainwindow.h \
    protocol.h \
    stage.h \
    protocolwindow.h \
    constants.h \
    database.h \
    savefileparser.h \
    rs232.h

FORMS    += \
    mainwindow.ui \
    protocolwindow.ui

RESOURCES += \
    img.qrc
