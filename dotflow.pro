#-------------------------------------------------
#
# Project created by QtCreator 2015-08-25T15:17:48
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dotflow
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    flowboard.cpp \
    flowcontext.cpp \
    flowcontextcontroller.cpp \
    winwidget.cpp \
    flowboardcontroller.cpp \
    gamewidget.cpp \
    levelwidget.cpp \
    levelitemwidget.cpp \
    hintswidget.cpp \
    flowsolver.cpp

HEADERS  += mainwindow.h \
    flowboard.h \
    flowcontext.h \
    flowcontextcontroller.h \
    winwidget.h \
    flowboardcontroller.h \
    gamewidget.h \
    levelwidget.h \
    levelitemwidget.h \
    hintswidget.h \
    flowsolver.h \
    globalconstant.h

FORMS    += mainwindow.ui \
    winwidget.ui \
    levelwidget.ui \
    levelitemwidget.ui \
    hintswidget.ui

RESOURCES += \
    gameinfo.qrc \
    fonts.qrc \
    sound.qrc \
    hints.qrc \
    icon.qrc

RC_ICONS = dotflow.icon
ICON = dotflow.icns
