TEMPLATE = app

QT += qml quick

CONFIG += c++11 qzxing_multimedia

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

include(../../src/QZXing.pri)

# Default rules for deployment.
include(deployment.pri)
