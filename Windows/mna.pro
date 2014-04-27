#-------------------------------------------------
#
# Project created by QtCreator 2014-04-23T14:49:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = mna
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    complexo.cpp \
    elementos.cpp \
    circuito.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    complexo.h \
    elementos.h \
    circuito.h \
    qcustomplot.h

FORMS    += mainwindow.ui
