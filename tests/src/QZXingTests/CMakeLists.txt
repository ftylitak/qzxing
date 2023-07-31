cmake_minimum_required(VERSION 3.1.0)

project(QZXingTests)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)

set(QZXING_USE_ENCODER ON)
set(QZXING_USE_DECODER_QR_CODE ON)
set(QZXING_USE_DECODER_1D_BARCODES ON)
set(QZXING_USE_DECODER_DATA_MATRIX ON)
set(QZXING_USE_DECODER_AZTEC ON)
set(QZXING_USE_DECODER_PDF17 ON)
set(QZXING_USE_DECODER_1D_BARCODES ON)
set(QZXING_MULTIMEDIA ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS
    Core Gui Quick Concurrent Multimedia
)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS
    Core Gui Quick Concurrent Multimedia REQUIRED
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../src qzxing)
include_directories(BEFORE SYSTEM
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../src/zxing
)

set(SOURCES
    main.cpp
    DecodeValidator.cpp
    ValidationStats.cpp
    EncodeValidator.cpp
    TestCase.cpp
    zxing/qrcode/encoder/MatrixUtilTests.cpp
    zxing/qrcode/encoder/MaskUtilTests.cpp
    zxing/qrcode/encoder/QRCodeTests.cpp
    zxing/qrcode/encoder/EncoderTests.cpp
    zxing/common/reedsolomon/ReedSolomonEncoderTests.cpp
    zxing/common/BitArrayTests.cpp
    zxing/qrcode/encoder/BitVectorTests.cpp
    EncoderStressTest.cpp
)

set(HEADERS
    DecodeValidator.h
    ValidationStats.h
    EncodeValidator.h
    TestCase.h
    zxing/qrcode/encoder/MatrixUtilTests.h
    zxing/qrcode/encoder/MaskUtilTests.h
    zxing/qrcode/encoder/QRCodeTests.h
    zxing/qrcode/encoder/EncoderTests.h
    zxing/common/reedsolomon/ReedSolomonEncoderTests.h
    zxing/common/BitArrayTests.h
    zxing/qrcode/encoder/BitVectorTests.h
    EncoderStressTest.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Concurrent
    Qt${QT_VERSION_MAJOR}::Multimedia
    qzxing
)
