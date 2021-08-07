#Author: Kang Lin(kl222@126.com)

SOURCE_DIR="`pwd`"
echo $SOURCE_DIR
TOOLS_DIR=${SOURCE_DIR}/Tools

cd ${TOOLS_DIR}

case "${BUILD_TARGERT}" in
    unix)
        if [ "$DOWNLOAD_QT" = "APT" ]; then
            export QT_ROOT=/usr/lib/`uname -m`-linux-gnu/qt5
        elif [ "$DOWNLOAD_QT" = "TRUE" ]; then
            QT_DIR=${TOOLS_DIR}/Qt/${QT_VERSION}
            export QT_ROOT=${QT_DIR}/${QT_VERSION}/gcc_64
        else
            #source /opt/qt${QT_VERSION_DIR}/bin/qt${QT_VERSION_DIR}-env.sh
            export QT_ROOT=/opt/qt${QT_VERSION_DIR}
        fi
        export PATH=$QT_ROOT/bin:$PATH
        export LD_LIBRARY_PATH=$QT_ROOT/lib/i386-linux-gnu:$QT_ROOT/lib:$LD_LIBRARY_PATH
    ;;
    android)
        export ANDROID_NDK_ROOT=`pwd`/android-ndk
        export ANDROID_NDK=$ANDROID_NDK_ROOT
    
        export ANDROID_SDK_ROOT=`pwd`/android-sdk
        export ANDROID_SDK=$ANDROID_SDK_ROOT
    
        QT_DIR=`pwd`/Qt/${QT_VERSION}
        export QT_ROOT=${QT_DIR}/${QT_VERSION}/android_armv7
    ;;
esac