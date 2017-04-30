TEMPLATE = app

QT += qml quick

CONFIG += c++11 qzxing_multimedia

CONFIG(debug, debug|release) {
    CONFIG+=qml_debug
} else {
    DEFINES += QT_NO_DEBUG
    DEFINES += QT_NO_DEBUG_OUTPUT
}

HEADERS += \
    application.h

SOURCES += main.cpp \
    application.cpp

RESOURCES += qml.qrc

include(../../src/QZXing.pri)

# Default rules for deployment.
include(deployment.pri)
