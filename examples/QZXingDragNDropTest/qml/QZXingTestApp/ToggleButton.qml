// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0

Rectangle {
    id: rect
    property alias text: label.text
    property bool isPressed: false

    width: label.width + 20
    height: label.height + 10
    border.color: "black"
    border.width: 1
    radius: 5

    property int decoderHint;

    Text{
        id: label
        color: "white"
        anchors.centerIn: parent
    }

    MouseArea{
        anchors.fill: parent
        onClicked: rect.isPressed = !rect.isPressed
    }

    states: [
        State{
            name: "pressed"
            when: isPressed
            PropertyChanges {target: rect; color:"gray"}
        },
        State{
            name: "normal"
            when: !isPressed
            PropertyChanges {target: rect; color:"darkgray"}
        }
    ]

    onIsPressedChanged: parent.updateDecoderHints(decoderHint)
}
