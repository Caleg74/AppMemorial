import QtQuick 2.0
import QtQuick.Controls 2.0
//import QtQuick.Particles 2.0

Item {
    property string text;
    property bool separatorVisible: true;
    property string imageSource;
    property int fontSize: 15;

    width: parent.width
    height: parent.height

    Row {
        width: parent.width
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter


        Text {
            id: titleItemName
            text: parent.parent.text
            font.pointSize: fontSize
            color: "#0a3f60"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            width: parent.width * 6 /10 - 2
            height: parent.height

        }

        Image {
            id: apparatusImage
            source: imageSource
            sourceSize.width: parent.width * 3 /10
            sourceSize.height: parent.width * 3 /10
            anchors.verticalCenter: parent.verticalCenter
        }

        Rectangle {
            id: separator
            width: 2    // just a line
            height: parent.height - 5
            color: "#d0d0d0"
            visible: separatorVisible
        }
    }
}
