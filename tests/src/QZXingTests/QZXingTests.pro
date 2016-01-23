QT += core
QT -= gui

CONFIG += gnu++11
QMAKE_CXXFLAGS += -std=gnu++11

TARGET = QZXingTests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    DecodeValidator.cpp \
    ValidationStats.cpp

HEADERS += \
    DecodeValidator.h \
    ValidationStats.h

include(../../../src/QZXing.pri)
