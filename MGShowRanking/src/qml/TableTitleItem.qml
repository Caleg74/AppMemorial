import QtQuick 2.0
import QtQuick.Controls 2.0
//import QtQuick.Particles 2.0

Item {
    property string text;
    property bool separatorVisible: true;
    property string imageSource;
    property int fontSize: 15;

//    width: parent.width
//    height: parent.height

    Item {  // some sort of a Row
//        width: parent.width
//        height: parent.height
//        anchors.verticalCenter: parent.verticalCenter
        anchors.fill: parent
        anchors.margins: 10

        Text {

            id: titleItemName
            text: parent.parent.text
            font.pointSize: fontSize
            color: "#0a3f60"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
//            width: parent.width - apparatusImage.width - separator.width
            height: parent.height
            anchors.left: parent.left
            anchors.right: apparatusImage.left

        }

        Image {
            id: apparatusImage
            source: imageSource
            width: parent.width * 3 /10
            sourceSize.width: width
            sourceSize.height: width
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: separator.left
        }

        Rectangle {
            id: separator
            width: 2    // just a line
            height: parent.height
            color: "#d0d0d0"
            visible: separatorVisible
            anchors.right: parent.right
        }
    }
}
