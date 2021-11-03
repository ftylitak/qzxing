import QtQuick 2.0
import QZXing 3.3

Rectangle {
    width: 360
    height: 360

    Rectangle{
        id:dropArea
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent.height-200


        DropArea{

            anchors.fill: parent
            onDropped: {
                console.log(drop.urls[0])

                var path = drop.urls[0];
                decoder.decodeImageFromFile(path)
            }
        }

        Text{
            anchors.centerIn: parent
            color: "gray"
            opacity: 0.8
            text: "Drag image to decode"
            elide: Text.ElideMiddle
            font.pixelSize: 30
        }

        Rectangle{
            id: decSelector
            width: parent.width -100
            height: parent.height/2
            clip:true

            color: "#00ffffff"

            anchors.horizontalCenter: parent.horizontalCenter

            property bool isFolded: true

            Rectangle{
                id: label
                color: "darkgray"
                border.color: "black"
                border.width: 1
                radius: 5

                width: decLabel.width + 20
                height: decLabel.height + 10

                anchors.left: parent.left
                anchors.bottom: parent.bottom

                anchors.margins: 2

                Text{
                    id: decLabel
                    text: "Active Decoders"
                    anchors.centerIn: parent
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: decSelector.isFolded = !decSelector.isFolded
                }
            }

            Rectangle{
                color: "darkgray"
                border.color: "black"
                border.width: 1
                radius: 5
                clip:true
                anchors.margins: 2

                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: label.top

                Flow{
                    id: flow
                    anchors.fill: parent
                    spacing: 10
                    anchors.margins: 5

                    property int hintSum: 0

                    move: Transition {
                        NumberAnimation {
                            properties: "x,y"
                            easing.type: Easing.OutCubic
                        }
                    }

                    ToggleButton{ text: "Aztec"; decoderHint: QZXing.DecoderFormat_Aztec}
                    ToggleButton{ text: "Codabar"; decoderHint: QZXing.DecoderFormat_CODABAR }
                    ToggleButton{ text: "Code_39"; decoderHint: QZXing.DecoderFormat_CODE_39 }
                    ToggleButton{ text: "Code_93"; decoderHint: QZXing.DecoderFormat_CODE_93 }
                    ToggleButton{ text: "Code_128"; decoderHint: QZXing.DecoderFormat_CODE_128 }
                    ToggleButton{ text: "Data Matrix"; decoderHint: QZXing.DecoderFormat_DATA_MATRIX }
                    ToggleButton{ text: "EAN_8"; decoderHint: QZXing.DecoderFormat_EAN_8 }
                    ToggleButton{ text: "EAN_13"; decoderHint: QZXing.DecoderFormat_EAN_13 }
                    ToggleButton{ text: "ITF"; decoderHint: QZXing.DecoderFormat_ITF }
                    ToggleButton{ text: "Maxicode"; decoderHint: QZXing.DecoderFormat_MAXICODE }
                    ToggleButton{ text: "PDF_417"; decoderHint: QZXing.DecoderFormat_PDF_417 }
                    ToggleButton{ text: "Qr Code"; decoderHint: QZXing.DecoderFormat_QR_CODE }
                    ToggleButton{ text: "RSS 14"; decoderHint: QZXing.DecoderFormat_RSS_14 }
                    ToggleButton{ text: "RSS expanded"; decoderHint: QZXing.DecoderFormat_RSS_EXPANDED }
                    ToggleButton{ text: "UPC A"; decoderHint: QZXing.DecoderFormat_UPC_A }
                    ToggleButton{ text: "UPC E"; decoderHint: QZXing.DecoderFormat_UPC_E }
                    ToggleButton{ text: "UPC EAN extension"; decoderHint: QZXing.DecoderFormat_UPC_EAN_EXTENSION }

                    function updateDecoderHints(hint)
                    {
                        //XOR operator to toggle the specific decoder
                        hintSum = hintSum ^ hint;
                        decoder.enabledDecoders = hintSum
                    }
                }
            }

            states:[
                State{
                    name: "folded"
                    when: decSelector.isFolded
                    PropertyChanges{target:decSelector; y: -decSelector.height+label.height}
                },
                State{
                    name: "unfolded"
                    when: !decSelector.isFolded
                    PropertyChanges{target:decSelector; y: 0}
                }
            ]

            Behavior on y {NumberAnimation{duration:250; easing.type: Easing.OutCubic}}
        }
    }

    QZXing{
        id: decoder
        //enabledDecoders: QZXing.DecoderFormat_QR_CODE
        //tryHarderType: QZXing.TryHarderBehaviour_Rotate //| QZXing.TryHarderBehaviour_ThoroughScanning
        imageSourceFilter: QZXing.SourceFilter_ImageNormal | QZXing.SourceFilter_ImageInverted

        onTagFound: {
            log.add("Tag found: " +tag+ ", milliseconds: " + processingTime)
        }
    }

    Rectangle{
        id: logRect
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: dropArea.bottom

        border.color: "gray"
        border.width: 1

        clip: true

        Flickable{
            anchors.fill: parent
            contentHeight: log.height
            contentWidth: log.width
            flickableDirection: Flickable.VerticalFlick


            TextEdit{
                id: log
                font.pointSize: 10
                width: logRect.width

                wrapMode: TextEdit.WordWrap

                function add(message)
                {
                    text = "=> " + message + "\n\n" + text;
                }
            }
        }
    }
}
