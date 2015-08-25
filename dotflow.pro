#-------------------------------------------------
#
# Project created by QtCreator 2015-08-25T15:17:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dotflow
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    flowboard.cpp \
    flowgameview.cpp \
    flowcontext.cpp \
    flowcontextcontroller.cpp

HEADERS  += mainwindow.h \
    flowboard.h \
    flowgameview.h \
    flowglobal.h \
    flowcontext.h \
    flowcontextcontroller.h

FORMS    += mainwindow.ui
