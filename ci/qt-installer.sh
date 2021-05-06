#!/bin/bash

#Author: Kang Lin(kl222@126.com)

#http://stackoverflow.com/questions/25105269/silent-install-qt-run-installer-on-ubuntu-server
#http://doc.qt.io/qtinstallerframework/noninteractive.html
#参考：https://github.com/benlau/qtci
#     https://github.com/rabits/dockerfiles
#     https://github.com/mjscosta/qt-silent-installer

set -e #quit on error

if [ $# -lt 2 ];
then
    echo qt-installer.sh qt-installer-file output_path
    exit -1
fi

function version_gt() { test "$(echo "$@" | tr " " "\n" | sort -V | head -n 1)" != "$1"; }
function version_le() { test "$(echo "$@" | tr " " "\n" | sort -V | head -n 1)" == "$1"; }
function version_lt() { test "$(echo "$@" | tr " " "\n" | sort -rV | head -n 1)" != "$1"; }
function version_ge() { test "$(echo "$@" | tr " " "\n" | sort -rV | head -n 1)" == "$1"; }

export PATH=$PATH:$PWD
export WORKDIR=$PWD
INSTALLER=$1
OUTPUT=$2
SCRIPT="$(mktemp /tmp/tmp.XXXXXXXXX)"

case $BUILD_ARCH in
    unix)
        SELECTEDPACKAGES=gcc_64
        ;;
    arm*|x86*)
        if version_ge $QT_VERSION_DIR 5.14 ; then
            SELECTEDPACKAGES=android
        else
            case $BUILD_ARCH in
                arm)
                    SELECTEDPACKAGES=android_armv7
                    ;;
                arm64)
                    SELECTEDPACKAGES=android_arm64_v8a
                    ;;
                x86)
                    SELECTEDPACKAGES=android_x86
                    ;;
                x86_64)
                    SELECTEDPACKAGES=android_x86_64
                    ;;
                *)
                    echo "Aach[$BUILD_ARCH] don't suppoert"
                    ;;
            esac
        fi
        ;;
    *)
        echo "Aach[$BUILD_ARCH] don't suppoert"
        ;;
esac

cat <<EOF > $SCRIPT
function Controller() {
    installer.autoRejectMessageBoxes();
    installer.installationFinished.connect(function() {
        gui.clickButton(buttons.NextButton);
    });
}

function log() {
    var msg = ["QTCI: "].concat([].slice.call(arguments));

    console.log(msg.join(" "));
}

Controller.prototype.WelcomePageCallback = function() {
    gui.clickButton(buttons.NextButton, 3000);
}

Controller.prototype.CredentialsPageCallback = function() {
    var login = installer.environmentVariable("QT_USER");
    var password = installer.environmentVariable("QT_PASSWORD");
    if( login === "" || password === "" ) {
        console.log("No credentials provided - could stuck here forever");
        gui.clickButton(buttons.CommitButton);
    }
    var widget = gui.currentPageWidget();
    widget.loginWidget.EmailLineEdit.setText(login);
    widget.loginWidget.PasswordLineEdit.setText(password);
    gui.clickButton(buttons.CommitButton);
}

Controller.prototype.ComponentSelectionPageCallback = function() {
    var components = installer.components();
    log("Available components: " + components.length);
    for (var i = 0 ; i < components.length ;i++) {
        log(components[i].name);
    }
    log("Select components");
    function trim(str) {
        return str.replace(/^ +/,"").replace(/ *$/,"");
    }
    var widget = gui.currentPageWidget();
    widget.deselectAll();
    var packages = trim("$SELECTEDPACKAGES").split(",");
    if (packages.length > 0 && packages[0] !== "") {
        
        for (var i in packages) {
            var pkg = trim(packages[i]);
            for (var i = 0 ; i < components.length ;i++) {
                if(components[i].name.indexOf(pkg) != -1)
                {
                    log("Select " + components[i].name);
                    widget.selectComponent(trim(components[i].name));
                }
            }
        }
    } else {
        log("Use default component list");
    }

    gui.clickButton(buttons.NextButton);
}

Controller.prototype.IntroductionPageCallback = function() {
    gui.clickButton(buttons.NextButton);
}


Controller.prototype.TargetDirectoryPageCallback = function() {
    var widget = gui.currentPageWidget();

    if (widget != null) {
        widget.TargetDirectoryLineEdit.setText("$OUTPUT");
    }

    gui.clickButton(buttons.NextButton);

}

Controller.prototype.LicenseAgreementPageCallback = function() {
    var widget = gui.currentPageWidget();

    if (widget != null) {
        widget.AcceptLicenseRadioButton.setChecked(true);
    }

    gui.clickButton(buttons.NextButton);
}

Controller.prototype.StartMenuDirectoryPageCallback = function() {
    gui.clickButton(buttons.CommitButton);
}

Controller.prototype.ReadyForInstallationPageCallback = function() {
    gui.clickButton(buttons.CommitButton);
}

Controller.prototype.FinishedPageCallback = function() {
    var widget = gui.currentPageWidget();
    widget.LaunchQtCreatorCheckBoxForm.launchQtCreatorCheckBox.setChecked(false);
    gui.clickButton(buttons.FinishButton);
}
EOF

chmod u+x $1
#显示log
$1 -v --script $SCRIPT
#不显示log
#$1 --script $SCRIPT