#-------------------------------------------------
#
# Project created by QtCreator 2018-03-23T19:58:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = PressureTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot/qcustomplot.cpp \
    createpdf.cpp

HEADERS  += mainwindow.h \
    qcustomplot/qcustomplot.h \
    data.h \
    createpdf.h

FORMS    += mainwindow.ui
