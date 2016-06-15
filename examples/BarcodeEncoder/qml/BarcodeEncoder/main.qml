import QtQuick 2.0
import QtQuick.Controls 1.1
import QZXing 2.3

Rectangle {
    width: 360
    height: 360

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
        text: "decode"
        anchors.margins: 10
        onClicked: {
            qzxing.encodeData(inputField.text)
            inputField.text = '';
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

        Image{
            id:resultImage
        }
    }

    QZXing {
        id: qzxing
    }
}
