TEMPLATE = app

CONFIG += qzxing_multimedia \
          enable_decoder_1d_barcodes \
          enable_decoder_qr_code \
          enable_decoder_data_matrix \
          enable_decoder_aztec \
          enable_decoder_pdf17

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

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

include(../../src/QZXing-components.pri)

# Default rules for deployment.
include(deployment.pri)

android {
    lessThan(QT_VERSION, 6.2) {
        HEADERS += \
            native.h

        SOURCES += \
            native.cpp

        QT += androidextras

        DISTFILES += \
            android/AndroidManifest.xml \
            android/gradle/wrapper/gradle-wrapper.jar \
            android/gradlew \
            android/res/values/libs.xml \
            android/build.gradle \
            android/gradle/wrapper/gradle-wrapper.properties \
            android/gradlew.bat \
            android/AndroidManifest.xml \
            android/gradle/wrapper/gradle-wrapper.jar \
            android/gradlew \
            android/res/values/libs.xml \
            android/build.gradle \
            android/gradle/wrapper/gradle-wrapper.properties \
            android/gradlew.bat

        ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
    }
}

else:ios {
  QMAKE_INFO_PLIST=Info.plist
}
