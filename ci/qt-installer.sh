#!/bin/bash

#http://stackoverflow.com/questions/25105269/silent-install-qt-run-installer-on-ubuntu-server
#http://doc.qt.io/qtinstallerframework/noninteractive.html
#参考：https://github.com/benlau/qtci
#     https://github.com/mjscosta/qt-silent-installer

set -e #quit on error

if [ $# -lt 2 ];
then
    echo qt-installer.sh qt-installer-file output_path
    exit -1
fi

export PATH=$PATH:$PWD
export WORKDIR=$PWD
INSTALLER=$1
OUTPUT=$2
SCRIPT="$(mktemp /tmp/tmp.XXXXXXXXX)"
case $BUILD_TARGERT in
    android_arm*)
        SELECTEDPACKAGES=android_armv7
        ;;
    android_x86)
        SELECTEDPACKAGES=android_x86
        ;;
    linux)
        SELECTEDPACKAGES=gcc_64
        ;;
       *)
       echo "Aach[$RABBIT_ARCH] don't suppoert"
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
    gui.clickButton(buttons.NextButton, 5000);
}

Controller.prototype.CredentialsPageCallback = function() {
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

$1 -v --script $SCRIPT

