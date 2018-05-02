#-------------------------------------------------
#
# Project created by QtCreator 2018-01-15T16:17:17
#
#-------------------------------------------------

QT       += core

QT       -= gui

DEFINES += noMCBC

TARGET = newt
CONFIG   += console
CONFIG   -= app_bundle
QT       += network

TEMPLATE = app


SOURCES += main.cpp \
    form1.cpp \
    form2.cpp \
    formdelay.cpp \
    master.cpp \
    formerror.cpp \
    udpsocket.cpp \
    settings.cpp \
    masterform2.cpp \
    form3.cpp \
    masterform3.cpp \
    calc.cpp \
    form4.cpp \
    masterform4.cpp \
    formstatus.cpp

INCLUDEPATH += ../../Mpks/MpksSettingsLib
LIBS +=-lnewt\
       -L../../Mpks/MpksSettingsLib -lMpksSettingsLib

HEADERS += \
    form1.h \
    form2.h \
    formdelay.h \
    master.h \
    data.h \
    formerror.h \
    udpsocket.h \
    settings.h \
    masterform2.h \
    form3.h \
    masterform3.h \
    calc.h \
    form4.h \
    masterform4.h \
    formstatus.h
