#!/bin/bash 
#Author: Kang Lin(kl222@126.com)

set -e
SOURCE_DIR="`pwd`"
echo $SOURCE_DIR
TOOLS_DIR=${SOURCE_DIR}/Tools
PACKAGE_DIR=${SOURCE_DIR}/Package
ThirdLibs_DIR=${TOOLS_DIR}/ThirdLibs

if [ ! -d "${TOOLS_DIR}" ]; then
    mkdir ${TOOLS_DIR}
fi
if [ ! -d "$PACKAGE_DIR" ]; then
    mkdir -p $PACKAGE_DIR
fi

function function_common()
{
    cd ${TOOLS_DIR}

    # See: https://github.com/benlau/qtci
    cd ${TOOLS_DIR}
    if [ "$DOWNLOAD_QT" = "TRUE" ]; then
        QT_DIR=`pwd`/Qt/${QT_VERSION}
        cd ${PACKAGE_DIR}
        if [ ! -d "${QT_DIR}" ]; then
            if [ "${QT_VERSION}" = "5.6.3" ]; then
                if [ ! -f qt-opensource-linux-x64-android-${QT_VERSION}.run ]; then
                    wget -c --no-check-certificate -nv http://download.qt.io/official_releases/qt/${QT_VERSION_DIR}/${QT_VERSION}/qt-opensource-linux-x64-android-${QT_VERSION}.run
                fi
                bash ${SOURCE_DIR}/ci/qt-installer.sh qt-opensource-linux-x64-android-${QT_VERSION}.run ${QT_DIR}
                #rm qt-opensource-linux-x64-android-${QT_VERSION}.run
            else
                if [ ! -f qt-opensource-linux-x64-${QT_VERSION}.run ]; then
                    wget -c --no-check-certificate -nv http://download.qt.io/official_releases/qt/${QT_VERSION_DIR}/${QT_VERSION}/qt-opensource-linux-x64-${QT_VERSION}.run
                fi
                bash ${SOURCE_DIR}/ci/qt-installer.sh qt-opensource-linux-x64-${QT_VERSION}.run ${QT_DIR}
                #rm qt-opensource-linux-x64-${QT_VERSION}.run
            fi
        fi
    fi
    
    cd ${SOURCE_DIR}
}

function install_android()
{
    if [ -n "$1" ]; then
        NDK="ndk-bundle"
    fi
    cd ${TOOLS_DIR}
    if [ ! -d "`pwd`/android-sdk" ]; then
        cd ${PACKAGE_DIR}
        ANDROID_STUDIO_VERSION=191.5900203
        if [ ! -f android-studio-ide-${ANDROID_STUDIO_VERSION}-linux.tar.gz ]; then
            wget -c -nv https://dl.google.com/dl/android/studio/ide-zips/3.5.1.0/android-studio-ide-${ANDROID_STUDIO_VERSION}-linux.tar.gz
        fi
        tar xzf android-studio-ide-${ANDROID_STUDIO_VERSION}-linux.tar.gz -C ${TOOLS_DIR}
        cd ${TOOLS_DIR}
        export JAVA_HOME=`pwd`/android-studio/jre
        export PATH=${JAVA_HOME}/bin:$PATH
        cd ${PACKAGE_DIR}
        SDK_PACKAGE=sdk-tools-linux-4333796.zip
        if [ ! -f ${SDK_PACKAGE} ]; then
            wget -c -nv https://dl.google.com/android/repository/${SDK_PACKAGE}
        fi
        cd ${TOOLS_DIR}
        mkdir android-sdk
        cd android-sdk
        unzip -q ${PACKAGE_DIR}/${SDK_PACKAGE} -d `pwd`
        
        echo "Install sdk and ndk ......"
        if [ -n "${ANDROID_API}" ]; then
            PLATFORMS="platforms;${ANDROID_API}"
        else
            PLATFORMS="platforms"
        fi
        if [ -z "${BUILD_TOOS_VERSION}" ]; then
            BUILD_TOOS_VERSION="28.0.3"
        fi
        (sleep 5 ; num=0 ; while [ $num -le 5 ] ; do sleep 1 ; num=$(($num+1)) ; printf 'y\r\n' ; done ) \
        | ./tools/bin/sdkmanager "platform-tools" "build-tools;${BUILD_TOOS_VERSION}" "${PLATFORMS}" ${NDK}
        if [ -n "${NDK}" ]; then
            if [ ! -d ${TOOLS_DIR}/android-ndk ]; then
                ln -s ${TOOLS_DIR}/android-sdk/ndk-bundle ${TOOLS_DIR}/android-ndk
            fi
        fi
    fi
}

function install_android_sdk_and_ndk()
{
    install_android
    NDK_PACKAGE=android-ndk-r21-linux-x86_64.zip
    cd ${PACKAGE_DIR}
    if [ ! -f ${NDK_PACKAGE} ]; then
        wget -c -nv https://dl.google.com/android/repository/${NDK_PACKAGE}
    fi
    unzip -q ${NDK_PACKAGE} -d ${TOOLS_DIR}
    cd ${TOOLS_DIR}
    mv android-ndk-r21 android-ndk
}

function function_android()
{
    cd ${TOOLS_DIR}
    
    sudo apt-get update -y -qq
    #sudo apt-get install -qq -y openjdk-11-jdk
    # install oracle jdk
    #sudo add-apt-repository ppa:linuxuprising/java -y
    #sudo apt update
    #(sleep 5 ; while true ; do sleep 1 ; printf '\r\n' ; done ) | sudo apt install oracle-java11-installer -qq -y
    
    #sudo apt install oracle-java11-set-default -qq -y
    #sudo apt-get install ant -qq -y
    sudo apt-get install libicu-dev -qq -y
    sudo apt-get install -qq -y libxkbcommon-x11-dev libglu1-mesa-dev

    install_android_sdk_and_ndk
    function_common

    cd ${SOURCE_DIR}
}

function function_unix()
{
    if [ "$DOWNLOAD_QT" != "TRUE" -a "$DOWNLOAD_QT" != "APT" ]; then
        #See: https://launchpad.net/~beineri
        sudo add-apt-repository ppa:beineri/opt-qt-${QT_VERSION}-`lsb_release -c|awk '{print $2}'` -y
    fi

    sudo apt-get update -y -qq
    sudo apt-get install debhelper fakeroot -y -qq
    sudo apt-get install -y -qq libglu1-mesa-dev \
        libxkbcommon-x11-dev \
        libpulse-mainloop-glib0 \
        libgstreamer1.0-dev \
        libgstreamer-plugins-base1.0-dev \
        gstreamer1.0-pulseaudio \
        libmysql-cil-dev libmysql-cil-dev libmysql-ocaml-dev \
        libmysql++-dev libmysqld-dev libmysqlcppconn-dev \
        libmysqlclient-dev \
        libodbc1 

    if [ "$DOWNLOAD_QT" = "APT" ]; then
        sudo apt-get install -y -qq qttools5-dev qttools5-dev-tools \
            qtbase5-dev qtbase5-dev-tools \
            qtmultimedia5-dev \
            qtquickcontrols2-5-dev \
            qtdeclarative5-dev \
            libqt5svg5-dev
        sudo ln -s /usr/lib/`uname -m`-linux-gnu/cmake /usr/lib/`uname -m`-linux-gnu/qt5/cmake 
    elif [ "$DOWNLOAD_QT" != "TRUE" ]; then
        sudo apt-get install -y -qq qt${QT_VERSION_DIR}base \
            qt${QT_VERSION_DIR}tools \
            qt${QT_VERSION_DIR}multimedia \
            qt${QT_VERSION_DIR}svg \
            qt${QT_VERSION_DIR}quickcontrols2 \
            qt${QT_VERSION_DIR}declarative
    fi
    function_common

    cd ${SOURCE_DIR}
}

function function_mingw()
{
    cd ${SOURCE_DIR}
    if [ "true" == "$RABBITIM_BUILD_THIRDLIBRARY" ]; then
        export RABBITIM_BUILD_CROSS_HOST=i686-w64-mingw32 #i586-mingw32msvc
    fi

    function_common
    cd ${SOURCE_DIR}
}

case ${BUILD_TARGERT} in
    android)
        function_android
        ;;
    unix)
        function_unix
        ;;
    windows_mingw)
        function_mingw
        ;;
    *)
    echo "There aren't ${BUILD_TARGERT}"
        ;;
esac

cd ${SOURCE_DIR}