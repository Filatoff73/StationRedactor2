#-------------------------------------------------
#
# Project created by QtCreator 2014-09-08T12:54:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StationRedactorNew
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    mainelement.cpp \
    blockrelay.cpp \
    view.cpp \
    contacts.cpp

HEADERS  += mainwindow.h \
    scene.h \
    mainelement.h \
    blockrelay.h \
    view.h \
    contacts.h

FORMS    += mainwindow.ui
