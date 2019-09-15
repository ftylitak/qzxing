#Author: KangLin(kl222@126.com)

SOURCE_DIR="`pwd`"
echo $SOURCE_DIR
TOOLS_DIR=${SOURCE_DIR}/Tools

cd ${TOOLS_DIR}

case "${BUILD_TARGERT}" in
    linux)
        QT_DIR=`pwd`/Qt/${QT_VERSION}
        export QT_ROOT=${QT_DIR}/${QT_VERSION}/gcc_64
    ;;
    android*)
        export ANDROID_NDK_ROOT=`pwd`/android-ndk
        export ANDROID_NDK=$ANDROID_NDK_ROOT
    
        export ANDROID_SDK_ROOT=`pwd`/android-sdk
        export ANDROID_SDK=$ANDROID_SDK_ROOT
    
        QT_DIR=`pwd`/Qt/${QT_VERSION}
        export QT_ROOT=${QT_DIR}/${QT_VERSION}/android_armv7
    ;;
esac
