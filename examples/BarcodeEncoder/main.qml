import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480

    ColumnLayout {
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
        GroupBox {
            Layout.fillWidth: true
            Layout.fillHeight: true
            title: "Result barcode image"
            clip: true
            Image{
                id:resultImage
                anchors.centerIn: parent
                source: "image://QZXing/qrcode/" + inputField.text
                cache: false;
            }
        }
    }
}
