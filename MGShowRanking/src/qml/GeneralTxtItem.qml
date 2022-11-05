import QtQuick 2.0
import QtQuick.Controls 2.0
//import QtQuick.Particles 2.0

Item {
    id: root
    property string generalText;
    property bool separatorVisible: true;
    property int fontSize: 15;
    property bool fontBold: false;

    width: parent.width
    height: parent.height

    Item {  // some sort of a Row
//        width: parent.width
//        height: parent.height
        anchors.fill: parent
        anchors.margins: 5

        Item {  // some sort of a Row
            width: parent.width
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
//            anchors.margins: 10
            anchors.left: parent.left
            anchors.right: separator.left

            Text {
                id: generalText
                renderType: Text.NativeRendering
                text: root.generalText
                font.pointSize: fontSize
                font.bold: fontBold
                color: "#0a3f60"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
//                width: parent.width - difficultyScore.width - separator.width
                height: parent.height
                anchors.left: parent.left
            }
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
