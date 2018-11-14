#!/bin/bash 
#Author: KangLin(kl222@126.com)

set -e

SOURCE_DIR="`pwd`"
echo $SOURCE_DIR
TOOLS_DIR=${SOURCE_DIR}/Tools
echo ${TOOLS_DIR}

if [ ! -f "${TOOLS_DIR}" ]; then
    mkdir -p ${TOOLS_DIR}
fi

function function_common()
{
    cd ${TOOLS_DIR}
    
    # Qt download and install：https://github.com/benlau/qtci  
    if [ -n "${QT_VERSION}" ]; then
        QT_DIR=`pwd`/Qt/${QT_VERSION}
        if [ ! -d "${QT_DIR}" ]; then
           wget -c --no-check-certificate -nv http://download.qt.io/official_releases/qt/${QT_VERSION_DIR}/${QT_VERSION}/qt-opensource-linux-x64-${QT_VERSION}.run
           bash ${SOURCE_DIR}/ci/qt-installer.sh qt-opensource-linux-x64-${QT_VERSION}.run ${QT_DIR}
           rm qt-opensource-linux-x64-${QT_VERSION}.run
        fi
    fi
}

function function_android()
{
    cd ${TOOLS_DIR}

    #Download android ndk  
    if [ ! -d "`pwd`/android-ndk" ]; then
        wget -c -nv http://dl.google.com/android/ndk/android-ndk-r10e-linux-x86_64.bin
        chmod u+x android-ndk-r10e-linux-x86_64.bin
        ./android-ndk-r10e-linux-x86_64.bin > /dev/null
        mv android-ndk-r10e android-ndk
        rm android-ndk-r10e-linux-x86_64.bin
    fi

    cd ${TOOLS_DIR}
    
    #Download android sdk  
    if [ ! -d "`pwd`/android-sdk" ]; then
        wget -c -nv https://dl.google.com/android/android-sdk_r24.4.1-linux.tgz
        tar xf android-sdk_r24.4.1-linux.tgz 
        mv android-sdk-linux android-sdk
        rm android-sdk_r24.4.1-linux.tgz 
        (sleep 5 ; while true ; do sleep 1 ; printf 'y\r\n' ; done ) \
        | android-sdk/tools/android update sdk -u -t tool,android-18,android-24,extra,platform,platform-tools,build-tools-25
    fi

    function_common
    cd ${SOURCE_DIR}
}

function function_linux()
{
    function_common

    cd ${SOURCE_DIR}
}

case ${BUILD_TARGERT} in
    android*)
        function_android
        ;;
    linux)
        function_linux
        ;;
    *)
    echo "There aren't ${BUILD_TARGERT}"
        ;;
esac

cd ${SOURCE_DIR}
