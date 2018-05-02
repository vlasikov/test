#-------------------------------------------------
#
# Project created by QtCreator 2018-01-09T14:31:53
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ncurses
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    terminal.cpp \
    window.cpp \
    form1.cpp \
    tbutton.cpp

LIBS +=-lncursesw

HEADERS += \
    terminal.h \
    window.h \
    form1.h \
    tbutton.h
