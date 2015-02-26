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


SOURCES += main.cpp \
    controller/imageupdater.cpp \
    gui/errordialog.cpp \
    gui/infoeagleeyedialog.cpp \
    gui/mainwindow.cpp \
    gui/showimagedialog.cpp \
    model/receiver/posdata.cpp \
    model/receiver/positioningreceiver.cpp \
    model/converter.cpp \
    model/line.cpp \
    model/ModelCreator.cpp


LIBS += `pkg-config opencv --libs`

RESOURCES += \
    image.qrc

HEADERS += \
    controller/imageupdater.h \
    gui/errordialog.h \
    gui/infoeagleeyedialog.h \
    gui/mainwindow.h \
    gui/showimagedialog.h \
    model/receiver/posdata.h \
    model/receiver/positioningreceiver.h \
    model/converter.h \
    model/line.h \
    model/ModelCreator.h

FORMS += \
    gui/errordialog.ui \
    gui/infoeagleeyedialog.ui \
    gui/mainwindow.ui \
    gui/showimagedialog.ui
