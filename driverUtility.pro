#-------------------------------------------------
#
# Project created by QtCreator 2016-02-04T09:59:31
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = driverUtility
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scanmanager.cpp \
    scanner.cpp \
    driversettings.cpp

HEADERS  += mainwindow.h \
    scanmanager.h \
    scanner.h \
    driversettings.h

FORMS    += mainwindow.ui
