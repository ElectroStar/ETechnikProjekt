#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T15:02:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerGui
TEMPLATE = app

#GUI
SOURCES += main.cpp\
    gui/mainwindow.cpp \
    gui/login.cpp \
    gui/guiFunctionClasses/drawimage.cpp \
    gui/guiFunctionClasses/playerstream.cpp \
    gui/guiFunctionClasses/playertracking.cpp \
    gui/guiFunctionClasses/converter.cpp \
    gui/cameracalibrationdialog.cpp \
    model/Calibrator/Calibrator.cpp \
    model/Calibrator/Settings.cpp \
    model/Filters/TailorFieldView.cpp \
    model/Filters/Undistorter.cpp \
    gui/errordialog.cpp


HEADERS  += gui/mainwindow.h \
    gui/login.h \
    gui/guiFunctionClasses/drawimage.h \
    gui/guiFunctionClasses/playerstream.h \
    gui/guiFunctionClasses/playertracking.h \
    gui/guiFunctionClasses/converter.h \
    gui/cameracalibrationdialog.h \
    model/Calibrator/Calibrator.h \
    model/Calibrator/Settings.h \
    model/Filters/ImageFilter.h \
    model/Filters/TailorFieldView.h \
    model/Filters/Undistorter.h \
    gui/errordialog.h


FORMS    += gui/mainwindow.ui \
    gui/login.ui \
    gui/cameracalibrationdialog.ui \
    gui/errordialog.ui


LIBS += `pkg-config opencv --libs`

RESOURCES += \
    gui/image.qrc
