TARGET = QZXingTests
CONFIG += console
CONFIG -= app_bundle

QT += concurrent

TEMPLATE = app

HEADERS += \
    DecodeValidator.h \
    ValidationStats.h \
    EncodeValidator.h \
    TestCase.h \
    zxing/qrcode/encoder/MatrixUtilTests.h \
    zxing/qrcode/encoder/MaskUtilTests.h \
    zxing/qrcode/encoder/QRCodeTests.h \
    zxing/qrcode/encoder/EncoderTests.h \
    zxing/common/reedsolomon/ReedSolomonEncoderTests.h \
    zxing/common/BitArrayTests.h \
    zxing/qrcode/encoder/BitVectorTests.h \
    EncoderStressTest.h
    #\backward.hpp

SOURCES += main.cpp \
    DecodeValidator.cpp \
    ValidationStats.cpp \
    EncodeValidator.cpp \
    TestCase.cpp \
    zxing/qrcode/encoder/MatrixUtilTests.cpp \
    zxing/qrcode/encoder/MaskUtilTests.cpp \
    zxing/qrcode/encoder/QRCodeTests.cpp \
    zxing/qrcode/encoder/EncoderTests.cpp \
    zxing/common/reedsolomon/ReedSolomonEncoderTests.cpp \
    zxing/common/BitArrayTests.cpp \
    zxing/qrcode/encoder/BitVectorTests.cpp \
    EncoderStressTest.cpp

include(../../../src/QZXing.pri)
