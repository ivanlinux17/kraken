#-------------------------------------------------
#
# Project created by QtCreator 2016-09-12T19:03:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kraken
TEMPLATE = app


SOURCES += main.cpp\
        kraken.cpp

HEADERS  += kraken.h \
    error.h

FORMS    += kraken.ui

win32: RC_ICONS = ../pics/octopus.ico
