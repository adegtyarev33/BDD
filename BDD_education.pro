#-------------------------------------------------
#
# Project created by QtCreator 2016-02-08T20:29:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BDD_education
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    function.cpp \
    graph.cpp \
    node.cpp

HEADERS  += mainwindow.h \
    function.h \
    graph.h \
    node.h

FORMS    += mainwindow.ui

CONFIG += c++11
