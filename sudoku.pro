#-------------------------------------------------
#
# Project created by QtCreator 2017-08-28T07:17:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sudoku
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logic.cpp

HEADERS  += mainwindow.h \
    logic.h \
    debug.h \
    const.h

FORMS    += mainwindow.ui
