import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtMultimedia 5.5

import QZXing 2.3

ApplicationWindow
{
    id: window
    visible: true
    width: 640
    height: 480
    title: "Qt QZXing Filter Test"

    Rectangle
    {
        id: bgRect
        color: "white"
        anchors.fill: videoOutput
    }

    Text
    {
        id: text1
        wrapMode: Text.Wrap
        font.pixelSize: 20
        anchors.top: parent.top
        anchors.left: parent.left
        z: 50
        text: "......"
    }

    Camera
    {
        id:camera
    }

    VideoOutput
    {
        id: videoOutput
        source: camera
        anchors.top: text1.bottom
        anchors.bottom: text2.top
        anchors.left: parent.left
        anchors.right: parent.right
     //   autoOrientation: true
        filters: [ zxingFilter ]
    }

    QZXingFilter
    {
        id: zxingFilter

        onDecodingStarted:
        {

        }

        onDecodingFinished:
        {
            if(succeeded)
            {

            }
            else
            {

            }
        }

        onTagFound:
        {
            console.log("--!!--");
            console.log(tag);
            text1.text = "--00--";
            text2.text = tag;
        }
    }

    Text
    {
        id: text2
        wrapMode: Text.Wrap
        font.pixelSize: 20
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        z: 50
        text: "Nothing yet..."
    }
}
