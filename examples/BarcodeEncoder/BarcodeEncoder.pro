# Add more folders to ship with the application, here
folder_01.source = qml/BarcodeEncoder
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

CONFIG += gnu++11
QMAKE_CXXFLAGS += -std=gnu++11

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp

# Installation path
# target.path =

include(../../src/QZXing.pri)

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()
