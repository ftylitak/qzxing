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
    ValidationStats.cpp \
    EncodeValidator.cpp \
    zxing/qrcode/encoder/MatrixUtilTests.cpp \
    zxing/qrcode/encoder/MaskUtilTests.cpp \
    zxing/qrcode/encoder/BitArrayTests.cpp

HEADERS += \
    DecodeValidator.h \
    ValidationStats.h \
    EncodeValidator.h \
    zxing/qrcode/encoder/MatrixUtilTests.h \
    TestCase.h \
    zxing/qrcode/encoder/MaskUtilTests.h \
    zxing/qrcode/encoder/BitArrayTests.h

include(../../../src/QZXing.pri)
