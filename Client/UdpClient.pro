#-------------------------------------------------
#
# Project created by QtCreator 2015-02-17T14:22:36
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UdpClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    positioningreceiver.cpp \
    posdata.cpp \
    guifunctionclasses/ModelCreator.cpp \
    guifunctionclasses/converter.cpp \
    imageupdater.cpp \
    infoeagleeyedialog.cpp \
    showimagedialog.cpp \
    errordialog.cpp

HEADERS  += mainwindow.h \
    positioningreceiver.h \
    posdata.h \
    guifunctionclasses/ModelCreator.h \
    guifunctionclasses/converter.h \
    imageupdater.h \
    infoeagleeyedialog.h \
    showimagedialog.h \
    errordialog.h

FORMS    += mainwindow.ui \
    infoeagleeyedialog.ui \
    showimagedialog.ui \
    errordialog.ui

LIBS += `pkg-config opencv --libs`

RESOURCES += \
    image.qrc
