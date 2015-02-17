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
    posdata.cpp

HEADERS  += mainwindow.h \
    positioningreceiver.h \
    posdata.h

FORMS    += mainwindow.ui
