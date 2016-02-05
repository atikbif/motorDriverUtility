#-------------------------------------------------
#
# Project created by QtCreator 2016-02-04T09:59:31
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = fan.ico
VERSION = 1.0.0.1
QMAKE_TARGET_COMPANY = Kontel Co
QMAKE_TARGET_PRODUCT = MotorUtility
QMAKE_TARGET_DESCRIPTION = Motor Driver Configurator
QMAKE_TARGET_COPYRIGHT = Kontel

CONFIG += c++11

TARGET = driverUtility
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scanmanager.cpp \
    scanner.cpp \
    driversettings.cpp \
    modbusrequest.cpp

HEADERS  += mainwindow.h \
    scanmanager.h \
    scanner.h \
    driversettings.h \
    modbusrequest.h

FORMS    += mainwindow.ui
