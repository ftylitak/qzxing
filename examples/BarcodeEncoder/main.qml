import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
//import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480

    minimumWidth: formatGroupBox.width +
                  errorCorrectionlevelGroupBox.width +
                  borderStatus.width +
                  transparentStatus.width +
                  5 * advancedOptions.spacing

    property bool isAdvancedOptionsEnabled: advancedSwitch.position;

    property string advancedUrl: "image://QZXing/encode/" + inputField.text +
                                 "?correctionLevel=" + errorCorrectionlevelCombo.currentText +
                                 "&format=" + formatCombo.currentText +
                                 "&border=" + (borderStatus.checkState !== Qt.Unchecked) +
                                 "&transparent=" + (transparentStatus.checkState !== Qt.Unchecked) +
                                 "&explicitSize=" + explicitSizeCombo.currentText

    property string normalUrl: "image://QZXing/encode/" + inputField.text

    ColumnLayout {
        id: mainLayout
        anchors {
            fill: parent
            margins: 10
        }

        TextArea {
            id: inputField
            Layout.fillWidth: true
            selectByMouse: true
            text: "Hello world!"

            Rectangle{
                anchors.fill: parent
                border.color: "#656565"
                border.width: 1
                color: "transparent"
            }
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
                id: explicitSizeGroupBox
                title: "Explicit Size"
                anchors.verticalCenter: parent.verticalCenter
                ComboBox {
                    id: explicitSizeCombo
                    model: ["auto", "60", "120", "240"]
                }
            }
        }

        Row {
            visible: mainWindow.isAdvancedOptionsEnabled
            CheckBox {
                id: borderStatus
                text: "Border"
            }

            CheckBox {
                id: colorPickerButton
                text: "Color"

                background: Rectangle {
                    color: barcodeRectangle.color
                }

                onCheckStateChanged: colorDialog.visible = true
            }

            CheckBox {
                id: transparentStatus
                text: "Transparent"
            }
        }

        Rectangle {
            id: barcodeRectangle
            Layout.fillWidth: true
            Layout.fillHeight: true
            border.width: 1
            border.color: "#bdbebf"
            clip: true
            color: "white"

            property int imageWidth: Math.min(height, width) * 0.7;

            Image{
                id:resultImage
                anchors.centerIn: parent
                sourceSize.width: 200
                sourceSize.height: 200

                source: mainLayout.getImageRequestString()
                cache: false;
            }
        }

        ColorDialog{
            id: colorDialog
            title: "Please choose a color"
            onAccepted: {
                barcodeRectangle.color = colorDialog.color
            }
        }

        function getImageRequestString() {
            if(mainWindow.isAdvancedOptionsEnabled)
                return advancedUrl;
            else
                return normalUrl;
        }
    }
}
