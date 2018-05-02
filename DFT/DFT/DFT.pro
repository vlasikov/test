#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T18:12:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = DFT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot/qcustomplot.cpp \
    dft.cpp

HEADERS  += mainwindow.h \
    qcustomplot/qcustomplot.h \
    data.h \
    dft.h

FORMS    += mainwindow.ui
