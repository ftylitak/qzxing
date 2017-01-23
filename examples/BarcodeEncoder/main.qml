import QtQuick 2.0
import QtQuick.Controls 2.0
import QZXing 2.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480

    TextField {
        id: inputField
        anchors.left: parent.left
        anchors.right: submit.left
        anchors.top: parent.top
        anchors.margins: 10
    }

    Button {
        id: submit
        anchors.right: parent.right
        anchors.top: parent.top
        text: "encode"
        anchors.margins: 10
        onClicked: {
            qzxing.encodeData(inputField.text)
            inputField.text = '';
            resultImage.source = "";
            resultImage.source = "image://QZXing/latestEncoded";
        }
    }

    GroupBox {
        anchors.top: inputField.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        title: "Result barcode image"
        clip: true

        Image{
            id:resultImage
            anchors.centerIn: parent
            cache: false;
        }
    }

    QZXing {
        id: qzxing
    }
}
