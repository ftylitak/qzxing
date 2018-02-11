import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480

    minimumWidth: formatGroupBox.width +
                  errorCorrectionlevelGroupBox.width +
                  sizeGroupBox.width +
                  6 * advancedOptions.spacing

    property bool isAdvancedOptionsEnabled: advancedSwitch.position;

    ColumnLayout {
        id: mainLayout
        anchors {
            fill: parent
            margins: 10
        }
        TextField {
            id: inputField
            Layout.fillWidth: true
            selectByMouse: true
            text: "Hello world!"
        }

        Row {
            Layout.fillWidth: true

            Label {
                id: resultLabel
                text: "Result barcode image"
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle {
                height: 1
                width: parent.width - resultLabel.width - advancedSwitch.width
            }

            Switch {
                id: advancedSwitch
                text: "Advanced"
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            id: advancedOptions
            Layout.fillWidth: true
            visible: mainWindow.isAdvancedOptionsEnabled
            clip: true

            spacing: 5

            GroupBox {
                id: formatGroupBox
                title: "Format"
                anchors.verticalCenter: parent.verticalCenter
                ComboBox {
                    id: formatCombo
                    model: ["qrcode"]
                }
            }

            GroupBox {
                id: errorCorrectionlevelGroupBox
                title: "Error Correction Level"
                anchors.verticalCenter: parent.verticalCenter
                ComboBox {
                    id: errorCorrectionlevelCombo
                    model: ["L", "M", "Q", "H"]
                }
            }

            GroupBox {
                id: sizeGroupBox
                anchors.verticalCenter: parent.verticalCenter
                title: "Size"
                GridLayout {
                    RadioButton {
                        id: radioButtonSize120
                        text: "120x120"
                    }
                    RadioButton {
                        id: radioButtonSize240
                        checked: true
                        text: "240x240"
                    }
                    RadioButton {
                        id: radioButtonSize320
                        text: "320x320"
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            border.width: 1
            border.color: "#bdbebf"
            clip: true

            Image{
                id:resultImage
                anchors.centerIn: parent

                source: mainLayout.getImageRequestString()
                cache: false;
            }
        }

        function getImageRequestString() {
            if(mainWindow.isAdvancedOptionsEnabled) {
                var width;
                var height;
                if (radioButtonSize120.checked) {width = "120"; height = "120"}
                else if (radioButtonSize240.checked) {width = "240"; height = "240"}
                else if (radioButtonSize320.checked) {width = "320"; height = "320"}

                return "image://QZXing/encode/" + inputField.text +
                            "?width="+width+
                            "&height="+height+
                            "&corretionLevel=" + errorCorrectionlevelCombo.currentText +
                            "&format=" + formatCombo.currentText
            }
            else
                return "image://QZXing/encode/" + inputField.text;
        }
    }
}
